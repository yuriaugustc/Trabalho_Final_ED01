#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TStack.h"
#include "imm.h"

int verify_format(char argv[], char aux[]){
    TStack *st;
    st = stack_create();
    for(int i = 0; i < strlen(argv); i++){
        stack_push(st, argv[i]);
    }
    for(int i = 2; i >= 0; i--){
        stack_top(st, &aux[i]);
        stack_pop(st);
    }
    return SUCCESS;
}

int imm_open_file(char argv[]){
    char aux[4];
    verify_format(argv, aux);
    if(!strcmp(aux, "txt")){
        printf("Conseguindo diferenciar txt do imm!\n");
    }
    else if(!strcmp(aux, "imm")){
        printf("Conseguindo diferenciar imm do txt!\n");
    }
    else{
        printf("This file don't have a suported format. Try format \".imm\" and \".txt\" files.\n");
    }
    return SUCCESS;
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