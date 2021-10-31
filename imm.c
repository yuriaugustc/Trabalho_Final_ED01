#include<stdio.h>
#include<string.h>
#include "Timm.h"

int main(int argc, char *argv[]){

    if(!strcmp(argv[1], "-open")){
        char aux[100];
        int i = 0;  
        strcpy(aux, argv[2]);
        i = imm_open_file(aux);
        if(i == INVALID_FORMAT_FILE){
            printf("This file don't have a suported format. Try format \".imm\" and \".txt\" files.\n");
        }
        return 0;
    }
    if(!strcmp(argv[1], "-convert")){
        imm_convert();
        return 0;
    }
    if(!strcmp(argv[1], "-segment")){
        imm_segment();
        return 0;
    }
    if(!strcmp(argv[1], "-cc")){
        imm_cc();
        return 0;
    }
    if(!strcmp(argv[1], "-lab")){
        imm_lab();
        return 0;
    }
    if(!strcmp(argv[1], "-help")){
        printf("\t\t\t\t---- imm list commands -----\n\n");
        // -open;
        printf("imm -open : \t\t\t\t\t\t");
        printf("Open an image (text format or binary format) and show the pixels value on the screen.\n\n");
        // -convert;
        printf("imm -convert [file.txt] [file.imm] : \t\t\t");
        printf("Convert an image on file.txt format to file.imm format.\n\n");
        // -segment;
        printf("imm -segment [thr] [file.imm] [segfile.imm] : \t\t");
        printf("Does a thresholding with a image thr value of file.mm.\n\t\t\t\t\t\t\t");
        printf("That can be used with .txt files also:\n \t\t\t\t\t\t\t\t");
        printf("\"imm -segment thr arq1.txt arq2.txt\"\n\t\t\t\t\t\t\t");
        printf("That can be used with .txt/.imm mixed files:\n \t\t\t\t\t\t\t\t");
        printf("\"imm -segment thr arq1.txt arq2.imm\" \n \t\t\t\t\t\t\t\t");
        printf("\"imm -segment thr arq1.imm arq2.txt\"\n\n");
        // -cc;
        printf("imm -cc [segfile.imm] [outfile.imm]: \t\t\t");
        printf("Detects an image connected components.\n\t\t\t\t\t\t\t");
        printf("That can be used with .txt and .imm files.\n\n");
        // -lab;
        printf("imm -lab [imlab.txt] [imlabout.txt]: \t\t\t");
        printf("Shows a path to go through in a labirint.\n\t\t\t\t\t\t\t");
        printf("That can be used with .txt and .imm files.\n\n");
    }
    else{
        printf("the command '%s' doesn't part of imm command list. try 'imm -help' to find some usable command.\n", argv[1]);
    }
    return 0;
}