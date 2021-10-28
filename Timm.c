#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    if(!strcmp(aux, "txt")){
        open_imm_file(argv);
        printf("Conseguindo diferenciar txt do imm!\n");
        return SUCCESS;
    }
    else if(!strcmp(aux, "imm")){
        printf("Conseguindo diferenciar imm do txt!\n");
        return SUCCESS;
    }
    else{
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