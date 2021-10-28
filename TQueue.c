#include <stdlib.h>
#include "TQueue.h"

struct TQueue{
    int qtd;
    QNode *head;
    QNode *end;
};

struct QNode{
    char data;
    QNode *next;
};

TQueue *queue_create(){
    TQueue *qe;
    qe = malloc(sizeof(TQueue));
    if (qe != NULL){
        qe->qtd = 0;
        qe->head = NULL;
        qe->end = NULL;
        return qe;
    }else{
        return NULL;
    }
}

int queue_free(TQueue *qe){
    if(qe == NULL){
        return INVALID_NULL_POINTER;
    }else{
        QNode *node = qe->head;
        QNode *aux;
        while (node->next != NULL){
            aux = node;
            node = node->next;
            free(aux);
        }
        free(qe);
        return SUCCESS;
    }
}

int queue_push(TQueue *qe, char ch){
    if(qe == NULL){
        return INVALID_NULL_POINTER;
    }else{
        QNode *node = malloc(sizeof(QNode));
        QNode *aux = qe->end;
        if(qe->qtd > 0){
            aux->next = node;
        }
        node->data = ch;
        node->next = NULL;
        qe->end = node;
        if(qe->head == NULL){
            qe->head = node;
        }
        (qe->qtd)++;
        return SUCCESS;
    }
}

int queue_pop(TQueue *qe){
    if(qe == NULL){
        return INVALID_NULL_POINTER;
    }else{
        QNode *aux = qe->head;
        qe->head = aux->next;
        (qe->qtd)--;
        free(aux);
        return SUCCESS;
    }
}

int queue_top(TQueue *qe, char *ch){
    if(qe == NULL){
        return INVALID_NULL_POINTER;
    }else{
        QNode *aux = qe->head;
        *ch = aux->data;
        return SUCCESS;
    }
}

int queue_empty(TQueue *qe){
    if(qe == NULL){
        return INVALID_NULL_POINTER;
    }else{
        if(qe->qtd > 0)
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