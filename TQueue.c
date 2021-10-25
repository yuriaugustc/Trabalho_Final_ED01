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
        return INVALID_NULL_POINTER;
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
        node->data = ch;
        aux->next = node;
        node->next = NULL;
        qe->end = node;
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
        *ch = qe->head->data;
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