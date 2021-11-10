#include <stdlib.h>
#include "TQueue.h"
 
struct TQueue{
    char *data;
    int qtd;
    int max;
};

TQueue *queue_create(){
    TQueue *qe;
    qe = malloc(sizeof(TQueue));
    if (qe != NULL){
        qe->max = 100;
        qe->qtd = 0;
        qe->data = calloc(qe->max, sizeof(char));
        if(qe->data == NULL){
            free(qe);
            return NULL;
        }
        return qe;
    }else{
        free(qe);
        return NULL;
    }
}

int queue_free(TQueue *qe){
    if(qe == NULL){
        return INVALID_NULL_POINTER;
    }else{
        free(qe);
        return SUCCESS;
    }
}

int queue_push(TQueue *qe, char ch){
    if(qe == NULL){
        return INVALID_NULL_POINTER;
    if (qe->qtd == qe->max) //fila cheia
        return FULL_QUEUE;
    }else{
        // deslocando os elementos
        for (int i = qe->qtd - 1; i >= 0; i--){
            qe->data[i + 1] = qe->data[i];
        }
        // primeira posição disponivel
        qe->data[0] = ch;
        qe->qtd++;
        return SUCCESS;
    }
}

int queue_pop(TQueue *qe){
    if(qe == NULL){
        return INVALID_NULL_POINTER;
    }else{
        (qe->qtd)--;
        return SUCCESS;
    }
}

int queue_top(TQueue *qe, char *ch){
    if(qe == NULL){
        return INVALID_NULL_POINTER;
    }else{
        *ch = qe->data[0];
        return SUCCESS;
    }
}

int queue_empty(TQueue *qe){
    if(qe == NULL){
        return INVALID_NULL_POINTER;
    }else{
        if(qe->qtd == 0)
            return EMPTY_QUEUE;
        else
            return NOT_EMPTY;
    }
}

int queue_size(TQueue *qe, int *qtd){
    if(qe == NULL){
        return INVALID_NULL_POINTER;
    }
    else{
        *qtd = qe->qtd;
        return SUCCESS;
    }
}