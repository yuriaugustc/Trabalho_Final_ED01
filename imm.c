#include<stdio.h>
#include<string.h>
#include "Timm.h"

int main(int argc, char *argv[]){
    //argv[0] = "imm";
    //argv[1] = "-convert";
    //argv[2] = "imagem.txt";
    //argv[3] = "imagem.imm";
    if(!strcmp(argv[1], "-open")){
        if(argc == 2){
            printf("To use \"-open\" command you need to pass a file to open with that command.\n");
            printf("Example: \"imm -open file.txt\" or \"imm -open file.imm\".\n");
            printf("Try \"imm -help\" to get more information.\n");
            return SUCCESS;
        }
        int i = 0;  
        i = imm_open_file(argv[2]);
        if(i == INVALID_FORMAT_FILE){
            printf("This file don't have a suported format. Try format \".imm\" and \".txt\" files.\n");
        }
        else if(i == INVALID_NULL_POINTER){
            printf("Wasn't possible open file. Please check the file integrity and try again.\n");
        }
        return SUCCESS;
    }
    if(!strcmp(argv[1], "-convert")){
        int i;
        if(argc <= 2){
            printf("To use \"-convert\" command you need to pass a file and a name to create a converted filed with that command.\n");
            printf("Example: \"imm -open file.txt converted_file\" or \"imm -open file.imm converted_file\".\n");
            printf("Try \"imm -help\" to get more information.\n");
            return SUCCESS;
        }
        else{
            i = imm_convert(argv[2], argv[3]); 
        }
        if(!i){
            printf("The file was be converted with success. Please check later for truly confimartion.\n");
        }
        else{
            printf("Something went wrong. Please check the file integrity and try again.\n");
        }
        return SUCCESS;
    }
    if(!strcmp(argv[1], "-segment")){
        imm_segment();
        return SUCCESS;
    }
    if(!strcmp(argv[1], "-cc")){
        imm_cc();
        return SUCCESS;
    }
    if(!strcmp(argv[1], "-lab")){
        imm_lab();
        return SUCCESS;
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
        return SUCCESS;
    }
    else{
       // printf("the command '%s' doesn't part of imm command list. try 'imm -help' to find some usable command.\n", argv[1]);
        return SUCCESS;
    }
}