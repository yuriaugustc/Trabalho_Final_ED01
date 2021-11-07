#include <stdlib.h>

void main(){
    system("gcc -c imm.c Timm.c TImg.c TStack.c TStckpt.c");// compilando todas os arquivos de extensão .c
    system("gcc imm.c Timm.o TImg.o TStack.o TStckpt.o -o imm"); // criando o executavel;
    system("del *.o "); // apagando os arquivos.o
}