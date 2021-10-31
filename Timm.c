#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TImg.h"
#include "TStack.h"
#include "Timm.h"

void verify_format(char argv[], char aux[]);
TImg *open_imm_file(char file[]);
TImg *open_txt_file(char file[]);

int imm_open_file(char argv[]){
    char aux[4];
    verify_format(argv, aux);
    TImg *img;
    if(!strcmp(aux, "txt")){
        printf("Conseguindo diferenciar txt do imm!\n");
        img = open_txt_file(argv); //acredito que esteja acontecendo segmentation fault;
        if(img == NULL){
            printf("Invalid Null Pointer\n");
        }
        img_print_matrix(img);
        return SUCCESS;
    }
    else if(!strcmp(aux, "imm")){
        printf("Conseguindo diferenciar imm do txt!\n");
        return SUCCESS;
    }
    else{
        printf("Texto verificado: %s\n", aux); // teste para verificar o que houve;
        return INVALID_FORMAT_FILE;
    }
}

int imm_convert(){
    printf("Okay, -convert convertendo fora da main ;w;\n");
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

TImg *tad_img_create(char file[]){ // funcao criada para evitar evitar repetição de codigo, atualmente utilizada pela open_txt e pela open_imm;
    FILE *tf;
    TImg *img;
    tf = fopen(file, "r");
    if(tf == NULL){
        return NULL;
    }
    char p = '0';
    int lin = 0, col = 1;
    while(p != EOF){ //este while serve para contar as linhas do arquivo para setar o TAD de imagem;
        p = fgetc(tf);
        if(p == '\n' || p == EOF){
            lin++; // um while só para a contabilidade de linhas pois se utilizar o contador de colunas em conjunto, o numero não será exato;
        }
    }
    rewind(tf); // colocando o ponteiro novamente ao inicio do arquivo, para ler uma linha inteira e contabilizar as colunas;
    p = '0'; // setando a variavel em zero para que a ultima leitura nao interfira no funcionamento do codigo;
    while(p != '\n'){ //este while conta as colunas do arquivo, por isso roda por apenas uma linha;
        p = fgetc(tf);
        if(p == '\t'){
            col++;
        }
    }
    fclose(tf);
    img = img_create(lin, col);
    if(img == NULL){
        return NULL;
    }
    return img;
}

TImg *open_txt_file(char file[]){ //funcao de abrir um arquivo de texto;
    FILE *tf;
    TImg *img;
    tf = fopen(file, "r");
    if(tf == NULL){
        return NULL;
    }
    img = tad_img_create(file);
    if(img == NULL){
        return NULL;
    }
    char value[] = "000";
    int i = 0, j = 0, val = 0;
    int v1 = 0, v2 = 0, v3 = 0, v4 = 0; 
    char p = '0'; //setando a variavel com zero para que a ultima leitura da variavel nao interfira no funcionamento do codigo;    
    while(p != EOF){ // o while verifica primeiro e depois lê o caractere;
        p = fgetc(tf);
        
        if((p != '\t' && p != EOF && p != '\n')){ // casos onde se leu caracteres de pixel;
            value[val] = p;
            val++;
        }
        if((p == '\t' || p == EOF || p == '\n')){ //casos onde foi encontrado o espaçamento de pixel, ou o fim do arquivo;
                                                     //o caso de EOF é verificado pois o ultimo pixel ficaria sem ser setado caso contrario ( ler comentario ao lado do while);
            if(val == 3 || val == 4){
                v1 = value[0] - '0'; //separando cada casa decimal por variavel, para ficar um pouco mais limpo o codigo;
                v2 = value[1] - '0'; 
                v3 = value[2] - '0'; // casos onde se leu 3 caracteres de pixel;
            }
            else if(val == 2){
                v1 = 0;
                v2 = value[0] - '0';
                v3 = value[1] - '0'; // casos onde se leu 2 caracteres de pixel;
            }
            else if(val == 1){
                v1 = 0;
                v2 = 0;
                v3 = value[0] - '0'; // casos onde se leu apenas 1 caractere de pixel;
            }
            v4 = (v1*100) + (v2*10) + (v3*1); //os pixels foram lidos como caractere, então deve-se convertê-los novamente ao seu valor;            
            img_set_value(img, i, j, v4);
            val = 0;
            value[0] = '0'; value[1] ='0'; value[2] = '0'; //zerando o vetor novamente para que o proximo pixel nao seja afetado(casos onde o pixel possui valor menor à 100, por exemplo);
            j++;
        }
    }
    fclose(tf);
    return img;
}

TImg *open_imm_file(char file[]){
    FILE *fb;
    fb = fopen(file, "rb");
    TImg *img;
    

    return img;
}