#include<stdio.h>
#include<string.h>
#include "Timm.h"

int main(int argc, char *argv[]){
    
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
            printf("Example: \"imm -convert file.txt name_converted_file.imm\" or \"imm -convert file.imm name_converted_file.txt\".\n");
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
        int i;
        if(argc <= 2){
            printf("To use \"-segment\" command you need to pass a number to do the thresholding, a file and a name to create a segmented filed with that command.\n");
            printf("Examples: \"imm -segment thr file.txt name_segmented_file.imm\"\n");
            printf("          \"imm -segment thr file.imm name_segmented_file.txt\"\n");
            printf("          \"imm -segment thr file.imm name_segmented_file.imm\"\n");
            printf("          \"imm -segment thr file.txt name_segmented_file.txt\"\n");
            printf("Try \"imm -help\" to get more information.\n");
            return SUCCESS;
        }
        else{
            int thr = 0;
            char th[] = "000";
            strcpy(th, argv[2]);
            if(strlen(th) == 3){
                thr = ((th[0] - '0')*100) + ((th[1] - '0')*10) + (th[2] - '0');
            }
            else if(strlen(th) == 2){
                thr = ((th[0] - '0')*10) + (th[1] - '0');
            }
            else if(strlen(th) == 1){
                thr = th[0] - '0';
            }
            if(thr >= 0 && thr <= 255){
                i = imm_segment(argv[3], argv[4], thr);
            }
            else{
                printf("This number of thresholding is invalid, pic a number between 0 and 255.\n");
                return SUCCESS;
            } 
        }
        if(!i){
            printf("The file was be segmented with success. Please check later for truly confimartion.\n");
        }
        else{
            printf("Something went wrong. Please check the file integrity and try again.\n");
        }
        return SUCCESS;
    }
    if(!strcmp(argv[1], "-cc")){
        if(argc <= 2){
            printf("To use \"-cc\" command you need to pass a file and a name to create a output file with that command.\n");
            printf("Example: \"imm -cc file_in.txt file_out.txt\" or \"imm -cc file_in.imm file_out.imm\".\n");
            printf("Try \"imm -help\" to get more information.\n");
        }else{
            int i = imm_cc(argv[2], argv[3]);
            if(!i){
                printf("The file was be created with success. Please check later for truly confimartion.\n");
            }
            else{
                printf("Something went wrong. Please check the file integrity and try again.\n");
            }
            return SUCCESS;
        }
    }
    if(!strcmp(argv[1], "-lab")){
        if(argc <= 2){
            printf("To use \"-lab\" command you need to pass a file and a name to create a output file with that command.\n");
            printf("Example: \"imm -lab file_in.txt file_out.txt\" or \"imm -lab file_in.txt file_out.txt\".\n");
            printf("Try \"imm -help\" to get more information.\n");
        }else{
            int i = imm_lab(argv[2], argv[3]);
            if(!i){
                printf("The file was be created with success. Please check later for truly confimartion.\n");
            }
            else{
                printf("Something went wrong. Please check the file integrity and try again.\n");
            }
        }
        return SUCCESS;
    }
    if(!strcmp(argv[1], "-help")){
        printf("\t\t\t\t----- imm list commands -----\n\n");
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
       printf("the command '%s' doesn't part of imm command list. try 'imm -help' to find some usable command.\n", argv[1]);
        return SUCCESS;
    }
}