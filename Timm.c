#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "TImg.h"
#include "TStack.h"
#include "Timm.h"

void verify_format(char argv[], char aux[]);
void convert_dec_2_bin(int dec, int *bin);
void convert_bin_2_dec(int bin, int *dec);
TImg *open_imm_file(char file[]);
TImg *open_txt_file(char file[]);

int imm_open_file(char *argv){
    char aux[4];
    verify_format(argv, aux);
    TImg *img;
    if(!strcmp(aux, "txt")){
        img = open_txt_file(argv); //criando a matriz a partir do arquivo.txt;
        if(img == NULL){
            return INVALID_NULL_POINTER;
        }
        img_print_matrix(img); // printando a matriz utilizada;
        img_free(img); //desalocando a matriz utilizada;
        return SUCCESS;
    }
    else if(!strcmp(aux, "imm")){
        img = open_imm_file(argv); //criando a matriz a partir do arquivo.txt;
        if(img == NULL){
            return INVALID_NULL_POINTER;
        }
        img_print_matrix(img); // printando a matriz utilizada;
        img_free(img); // desalocando a matriz utilizada;
        return SUCCESS;
    }
    else{
        printf("Texto verificado: %s\n", aux); // teste para verificar o que houve;
        return INVALID_FORMAT_FILE;
    }
}

int imm_convert(char *file, char *bin){
    char aux[4];
    verify_format(file, aux);
    if(!strcmp(aux, "txt")){
        TImg *img = open_txt_file(file);
        if(img == NULL){
            return INVALID_NULL_POINTER;
        }
        FILE *bf = fopen(bin, "wb");
        if(bf == NULL){
            return INVALID_NULL_POINTER;
        }
        int lin = 0, col = 0, value = 0, c1 = 0, l1 = 0, i = 0, j = 0;      // criando variaveis auxiliares de linha e colunas pois a originais estao sendo usadas no for aninhado;                 
        lin = img_get_line(img);        // obtendo o numero de linhas do arquivo;
        fwrite(&lin, sizeof(int), 1, bf);     // inserindo o numero de linhas no inicio do arquivo binario;
        col = img_get_columns(img);     // obtendo o numero de colunas do arquivo;
        fwrite(&col, sizeof(int), 1, bf);     // inserindo o numero de colunas no inicio do arquivo binario;
        for(j = 0; j < lin*col; j++){
            img_get_value(img, i, j, &value);
            fwrite(&value, sizeof(int), 1, bf);
        }
        open_imm_file("img.imm");
        img_free(img); // desalocando o TADImg em formato txt;
        fclose(bf);
    }
    else{
        return INVALID_FORMAT_FILE;
    }
    return SUCCESS;
}

int imm_segment(){
    printf("Okay, -segment segmentando fora da main ;w;\n");
    return SUCCESS;
}

int imm_cc(){
    printf("Okay, -cc cczando fora da main ;w;\n");
    return SUCCESS;
}

int imm_lab(){
    printf("Okay, -lab labindo fora da main ;w;\n");
    return 0;
}

void convert_dec_2_bin(int dec, int *bin){ //criei essa funcao achando que precisava converter para binario antes de usar fwrite ;-;
    int aux = 0, j = 0, vet[9];
    *bin = 0;
    while(dec != 0 && dec != 1){ // este while serve para achar a representação binaria, separando cada digito em uma posição do vetor para saber o tamanho do digito;
        aux = dec % 2;
        dec = dec / 2;
        vet[j] = aux;
        j++;
    }
    vet[j] = dec;
    for(int i = j; i >= 0; i--){    // este for serve para colocar os digitos em suas devidas casaa decimais;
        *bin += (vet[i] * trunc(pow(10, i)));  //truncate pois estava com problemas de arredondamento, por exemplo o caso 255 ficaria em 11111110;
    }
}

void convert_bin_2_dec(int bin, int *dec){ 
    int count = 0;
    int vet[9], i = 0;
    *dec = 0;
    while(bin > 9){         // laço para separar o digitos binarios e contá-los;
        count++;
        vet[i] = bin % 10;
        bin /= 10;
        i++;
    }
    vet[i] = bin;
    for(int j = 0; j <= i; j++){        // este for serve para potenciar os digitos separados devidamente em suas posicoes;
        *dec += (vet[j] * pow(2, j));
    }
}

void verify_format(char argv[], char aux[]){
    TStack *st;
    st = stack_create();
    for(int i = 0; i < strlen(argv); i++){
        stack_push(st, argv[i]);
    }
    aux[3] = '\0';
    for(int i = 2; i >= 0; i--){
        stack_top(st, &aux[i]);
        stack_pop(st);
    }
    stack_free(st);
}

TImg *open_txt_file(char file[]){ //funcao de abrir um arquivo de texto;
    FILE *tf;
    TImg *img;
    tf = fopen(file, "r");
    if(tf == NULL){
        return NULL;
    }
    char p = '0';
    int lin = 0, col = 1;
    while(p != EOF){        //este while serve para contar as linhas e colunas do arquivo para alocar o TAD de imagem;
        p = fgetc(tf);
        if(p == '\n' || p == EOF){  // verificacao de linhas;
            lin++; 
        }
        if(lin == 0 && p == '\t'){  // verificacao de colunas. Só será executado na primeira linha;
            col++;
        }
    }
    rewind(tf);
    img = img_create(lin, col);
    if(img == NULL){
        return NULL;
    }
    char value[] = "000";
    int i = 0, j = 0, val = 0;
    int v1 = 0, v2 = 0, v3 = 0, v4 = 0; 
    p = '0';          //setando a variavel com zero para que a ultima leitura da variavel nao interfira no funcionamento do codigo;    
    while(p != EOF){  // o while verifica primeiro e depois lê o caractere;
        p = fgetc(tf);
        
        if((p != '\t' && p != EOF && p != '\n')){ // casos onde se leu caracteres de pixel;
            value[val] = p;
            val++;
        }
        if((p == '\t' || p == EOF || p == '\n')){ //casos onde foi encontrado o espaçamento de pixel, ou o fim do arquivo, o caso de EOF é verificado pois o ultimo pixel ficaria sem ser setado caso contrario ( ler comentario ao lado do while);
            if(val == 3 || val == 4){
                v1 = value[0] - '0';        //separando cada casa decimal por variavel, para ficar um pouco mais limpo o codigo;
                v2 = value[1] - '0'; 
                v3 = value[2] - '0';        // casos onde se leu 3 caracteres de pixel;
            }
            else if(val == 2){
                v1 = 0;
                v2 = value[0] - '0';
                v3 = value[1] - '0';                        // casos onde se leu 2 caracteres de pixel;
            }
            else if(val == 1){
                v1 = 0;
                v2 = 0;
                v3 = value[0] - '0';                        // casos onde se leu apenas 1 caractere de pixel;
            }
            v4 = (v1*100) + (v2*10) + (v3*1);               //os pixels foram lidos como caractere, então deve-se convertê-los novamente ao seu valor;            
            img_set_value(img, i, j, v4);
            val = 0;
            value[0] = '0'; value[1] ='0'; value[2] = '0';  //zerando o vetor novamente para que o proximo pixel nao seja afetado(casos onde o pixel possui valor menor à 100, por exemplo);
            j++;
        }
    }
    fclose(tf);
    return img;
}

TImg *open_imm_file(char file[]){       // binario com erro, nao sei se é a leitura ou a conversao de txt para binario;
    FILE *bf;
    bf = fopen(file, "rb");
    if(bf == NULL){
        return NULL;
    }
    int lin = 0;
    fread(&lin,sizeof(int), 1, bf);  // lendo o numero de linhas do arquivo binario, gravado por padrao no primeiro bloco de memoria do arquivo.
    int col = 0;
    fread(&col,sizeof(int), 1, bf);  // lendo o numero de colunas do arquivo binario, gravado por padrao no segundo bloco de memoria do arquivo;
    TImg *img = img_create(lin, col); 
    if(img == NULL){
        return NULL;
    }
    int aux = 0, i = 0, j = 0;
    for(j = 0; j < lin*col; j++){
        fread(&aux,sizeof(int), 1, bf); // lendo o bloco de memoria correspondente ao pixel;
        img_set_value(img, i, j, aux);  // inserindo o numero decimal no tad de imagem;
    }
    return img;
}