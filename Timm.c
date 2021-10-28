#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TImg.h"
#include "TStack.h"
#include "Timm.h"

void verify_format(char argv[], char aux[]){
    TStack *st;
    st = stack_create();
    for(int i = 0; i < strlen(argv); i++){
        stack_push(st, argv[i]);
    }
    for(int i = 2; i >= 0; i--){
        stack_top(st, &aux[i]);
        stack_pop(st);
    }
    stack_free(st);
}

TImg *open_imm_file(char file[]){
    
}

TImg *open_txt_file(char file[]){
    FILE *tf;
    TImg *img;
    img = img_create(1000, 1000);
    tf = fopen(file, "r");
    if(tf == NULL){
        return NULL;
    }
    char *aux;
    char print[1000], value[4] = "000";
    int i = 0, val = 0;
    while(!feof(tf)){ //lê o arquivo enquanto não encontra o fim de arquivo
        aux = fgets(print, 1000, tf);
        if(aux){ //confirma se foi possivel ler a linha
            for(int j = 0; j < strlen(print); j++){
                if(print[j] == '\n'){
                    img_set_value(img, i, j, -1); //como o TAD de imagem foi criado como valores int, criarei uma coluna a mais que terá valor -1, representando onde ocorrerá a quebra de linha ao ser printado na tela;
                    break;
                }
                else if(print[j] != ' '){ //verifica se acha algum espaço, enquanto não acha espaço, preenche o vetor auxiliar com o valor do pixel
                    value[val] = print[j];
                    val++;
                }
                else if(print[j] == ' '){
                    int v1 = (int)print[0], v2 = (int)print[1], v3 = (int)print[2]; //separando cada casa decimal por variavel, para fica um pouco mais limpo o codigo;
                    int v4 = (v1*100)+(v2*10)+(v3*1); //os pixels foram lidos como caractere, então deve-se convertê-los novamente ao seu valor;
                    img_set_value(img, i, j, v4);
                    val = 0;
                    value[0] = '0'; value[1] ='0'; value[2] = '0'; //zerando o vetor novamente para que o proximo pixel nao seja afetado(casos onde o pixel possui valor menor à 100, por exemplo);
                    i++;
                }
            }
        }
    }
    fclose(tf);
    return img;
}

char *open_imm_file(char file[]){
    FILE *fb;
    fb = fopen(file, "r");
    int aux = 0;
    char print[1000], *p;
    *p = &print;
    while(aux != EOF){
        aux = fscanf(fb, "%[^\n]s", print);
    }
    return p;
}

int open_txt_file(){

}

int imm_open_file(char argv[]){
    
    char aux[4];
    verify_format(argv, aux);
    TImg *img; //não sei pq diabos está dando erro;
    if(!strcmp(aux, "txt")){
        open_imm_file(argv);
        printf("Conseguindo diferenciar txt do imm!\n");
        img = open_txt_file; // o compilador fala que estou passando um ponteiro de tipo diferente aqui.
        return SUCCESS;
    }
    else if(!strcmp(aux, "imm")){
        printf("Conseguindo diferenciar imm do txt!\n");
        return SUCCESS;
    }
    else{
        printf("%s", aux); // teste para verificar o que houve;
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