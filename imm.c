#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]){

    if(strcmp(argv[1], "-open") == 0){
        
        
        if(strcmp(aux, ".txt") == 0){
            printf("Okay, -open abrindo ;w;\n");
        }
        return 0;
    }
    if(strcmp(argv[1], "-convert") == 0){
        printf("Okay, -convert convertendo ;w;\n");
        return 0;
    }
    if(strcmp(argv[1], "-segment") == 0){
        printf("Okay, -segment segmentando ;w;\n");
        return 0;
    }
    if(strcmp(argv[1], "-cc") == 0){
        printf("Okay, -cc cczando ;w;\n");
        return 0;
    }
    if(strcmp(argv[1], "-lab") == 0){
        printf("Okay, -lab labindo ;w;\n");
        return 0;
    }
    else{
        printf("the command '%s' doesn't part of imm's mount command. try 'imm -help' to find some usable command.\n", argv[1]);
    }
}