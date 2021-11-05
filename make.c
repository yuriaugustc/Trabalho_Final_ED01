#include <stdlib.h>

void main(){
    system("gcc -c imm.c Timm.c TImg.c Tstack.c");// compilando todas os arquivos de extensão .c
    system("gcc imm.c Timm.o TImg.o TStack.o -o imm"); // criando o executavel;
    system("del *.o "); // apagando os arquivos.o
}