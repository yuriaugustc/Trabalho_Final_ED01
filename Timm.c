#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "TImg.h"
#include "TStack.h"
#include "Timm.h"

void verify_format(char argv[], char aux[]);
int segment_bin_2_bin(char *file, char *bin, int thr);
int segment_txt_2_txt(char *file, char *bin, int thr);
int convert_txt_2_bin(char *file, char *bin, int thr);
int convert_bin_2_txt(char *file, char *bin, int thr);
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
    int i;
    verify_format(file, aux);
    if(!strcmp(aux, "txt")){     //conversao de bin para txt;
        i = convert_txt_2_bin(file, bin, -1);
        if(!i){
            return SUCCESS;
        }else{
            return INVALID_FORMAT_FILE;
        }
    }
    else if(aux, "imm"){         // conversao de imm para txt;
        i = convert_bin_2_txt(file, bin, -1);
        if(!i){
            return SUCCESS;
        }else{
            return INVALID_FORMAT_FILE;
        }
    }
    else{
        return INVALID_FORMAT_FILE;
    }
}

int imm_segment(char *file, char *bin, int thr){
    char file1[4], file2[4];
    int i;
    verify_format(file, file1); // verificando o formato dos dois arquivos
    verify_format(bin, file2);

    if(!strcmp(file1, "txt")){
        if(!strcmp(file2, "txt")){
            i = segment_txt_2_txt(file, bin, thr);
        }else{
            i = convert_txt_2_bin(file, bin, thr);
        }
    }else if(!strcmp(file1, "imm")){
        if(!strcmp(file2, "imm")){
            i = segment_bin_2_bin(file, bin, thr);
        }else{
            i = convert_bin_2_txt(file, bin, thr);
        }
    }
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

int convert_txt_2_bin(char *file, char *bin, int thr){
    int v0 = 0, v1 = 1;
    TImg *img = open_txt_file(file);
    if(img == NULL){
        return INVALID_NULL_POINTER;
    }
    FILE *bf = fopen(bin, "wb");
    if(bf == NULL){
        return INVALID_NULL_POINTER;
    }
    int lin = 0, col = 0, value = 0, i = 0, j = 0;      // criando variaveis auxiliares de linha e colunas pois a originais estao sendo usadas no for aninhado;                 
    lin = img_get_line(img);        // obtendo o numero de linhas do arquivo;
    fwrite(&lin, sizeof(int), 1, bf);   // inserindo o numero de linhas no inicio do arquivo binario;
    col = img_get_columns(img);     // obtendo o numero de colunas do arquivo;
    fwrite(&col, sizeof(int), 1, bf);   // inserindo o numero de colunas no inicio do arquivo binario;
    for(j = 0; j < lin*col; j++){
        img_get_value(img, i, j, &value);
        if(thr == -1){                  // re-utilização de codigo, -1 é codigo nulo para o comando open utilizar a mesma funcao sem sofrer limiarizacao;
            fwrite(&value, sizeof(int), 1, bf);
        }else{
            if(value > thr){                    //thresholding : se é maior que thr, acessa o endereco de uma variavel com valor 1 e escreve no arquivo;
                fwrite(&v1, sizeof(int), 1, bf);    //fiquei na duvida se caso eu inserisse dentro do fwrite o valor "1", se ele funcionaria ou se ele procuraria o que está no endereço 1;
            }else{                              //thresholding : se é menor que thr, acessa o endereco de uma variavel com valor 0 e escreve no arquivo;
                fwrite(&v0, sizeof(int), 1, bf);    // mesma duvida do fwrite anterior;
            }
        }
    }
    img_free(img); // desalocando o TADImg;
    fclose(bf);    // fechando o arquivo;
    return SUCCESS;
}

int convert_bin_2_txt(char *bin, char *file, int thr){
    TImg *img = open_imm_file(bin);
    if(img == NULL){
        return INVALID_NULL_POINTER;
    }
    FILE *tf = fopen(file, "w");
    if(tf == NULL){
        return INVALID_NULL_POINTER;
    }
    int lin = img_get_line(img);      // obtendo o numero de linhas do arquivo;
    int col = img_get_columns(img);   // obtendo o numero de colunas do arquivo;
    int value = 0, i = 0, j = 0;                 
    for(j = 0; j < lin*col; j++){
        img_get_value(img, i, j, &value);
        if(thr == -1){              // re-utilização de codigo, -1 é um codigo nulo para o comando open utilizar a mesma funcao sem sofrer limiarizacao;
            fprintf(tf, "%d\t", value);
        }else{
            if(value > thr){                    //thresholding : se é maior que thr, acessa o endereco de uma variavel com valor 1 e escreve no arquivo;
                fprintf(tf, "1\t");    
            }
            else{                               //thresholding : se é maior que thr, acessa o endereco de uma variavel com valor 1 e escreve no arquivo;
                fprintf(tf, "0\t");
            }
        }
        if((j/col-1) == 0){
            fprintf(tf, "\n");
        }
    }
    img_free(img); // desalocando o TADImg;
    fclose(tf);    // fechando o arquivo;
    return SUCCESS;
}

int segment_bin_2_bin(char *file, char *bin, int thr){
    int v0 = 0, v1 = 1;
    TImg *img = open_txt_file(file);
    if(img == NULL){
        return INVALID_NULL_POINTER;
    }
    FILE *bf = fopen(bin, "wb");
    if(bf == NULL){
        return INVALID_NULL_POINTER;
    }
    int lin = 0, col = 0, value = 0, i = 0, j = 0;      // criando variaveis auxiliares de linha e colunas pois a originais estao sendo usadas no for aninhado;                 
    lin = img_get_line(img);        // obtendo o numero de linhas do arquivo;
    fwrite(&lin, sizeof(int), 1, bf);   // inserindo o numero de linhas no inicio do arquivo binario;
    col = img_get_columns(img);     // obtendo o numero de colunas do arquivo;
    fwrite(&col, sizeof(int), 1, bf);   // inserindo o numero de colunas no inicio do arquivo binario;
    for(j = 0; j < lin*col; j++){
        img_get_value(img, i, j, &value);
        if(thr == -1){                  // re-utilização de codigo, -1 é codigo nulo para o comando open utilizar a mesma funcao sem sofrer limiarizacao;
            fwrite(&value, sizeof(int), 1, bf);
        }else{
            if(value > thr){                    //thresholding : se é maior que thr, acessa o endereco de uma variavel com valor 1 e escreve no arquivo;
                fwrite(&v1, sizeof(int), 1, bf);    //fiquei na duvida se caso eu inserisse dentro do fwrite o valor "1", se ele funcionaria ou se ele procuraria o que está no endereço 1;
            }else{                              //thresholding : se é menor que thr, acessa o endereco de uma variavel com valor 0 e escreve no arquivo;
                fwrite(&v0, sizeof(int), 1, bf);    // mesma duvida do fwrite anterior;
            }
        }
    }
    img_free(img); // desalocando o TADImg;
    fclose(bf);    // fechando o arquivo;
    return SUCCESS;
}

int segment_txt_2_txt(char *file, char *bin, int thr){
    TImg *img = open_imm_file(file);
    if(img == NULL){
        return INVALID_NULL_POINTER;
    }
    FILE *tf = fopen(bin, "w");
    if(tf == NULL){
        return INVALID_NULL_POINTER;
    }
    int lin = img_get_line(img);      // obtendo o numero de linhas do arquivo;
    int col = img_get_columns(img);   // obtendo o numero de colunas do arquivo;
    int value = 0, i = 0, j;                 
    for(j = 0; j < lin*col; j++){
        img_get_value(img, i, j, &value);
        if(thr == -1){                // re-utilização de codigo, -1 é um codigo nulo para o comando open utilizar a mesma funcao sem sofrer limiarizacao;
            fprintf(tf, "%d\t", value);
        }else{
            if(value > thr){          //thresholding : se é maior que thr, acessa o endereco de uma variavel com valor 1 e escreve no arquivo;
                fprintf(tf, "1\t");    
            }
            else{                     //thresholding : se é maior que thr, acessa o endereco de uma variavel com valor 1 e escreve no arquivo;
                fprintf(tf, "0\t");
            }
        }
        if((j/col-1) == 0){
            fprintf(tf, "\n");
        }
    }
    img_free(img); // desalocando o TADImg;
    fclose(tf);    // fechando o arquivo;
    return SUCCESS;
}