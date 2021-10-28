#include <stdio.h>
#include "TQueue.h"

int main(){
    TQueue *fila;

    fila = queue_create();
    queue_push(fila, 'h');
    queue_push(fila, 'e');
    queue_push(fila, 'l');
    queue_push(fila, 'l');
    queue_push(fila, 'o');
    queue_push(fila, '!');
    queue_push(fila, '!');
    queue_push(fila, '\0');

}