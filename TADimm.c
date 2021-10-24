#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imm.h"


int imm_open_file(){
    printf("Okay, -open abrindo fora da main ;w;\n");
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