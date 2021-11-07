#include <stdlib.h>
#include "TStckpt.h"

struct TStckpt{
    int max;
    int qtd;
    point *pt;
};

TStckpt *stckpt_create(){
    TStckpt *st = malloc(sizeof(TStckpt));
        st->qtd = 0;
        st->max = 100;
        st->pt = malloc(st->max*sizeof(point));
        if (st->pt == NULL){
            free(st);
            return NULL;
        }
    return st;
}

int stckpt_realloc(TStckpt *st){
    if(st == NULL)
        return INVALID_NULL_POINTER;
    else{
        TStckpt *aux = malloc(sizeof(TStckpt));
        aux->pt = malloc(aux->max*2*sizeof(point));
        for(int i = 0; i < st->qtd; i++){
            aux->pt[i] = st->pt[i];
        }
        free(st); // desalocando a pilha antiga;
        st = aux; // apontando para a nova pilha;
        return SUCCESS;
    }
}

int stckpt_free(TStckpt *st){
    if(st == NULL){
        return INVALID_NULL_POINTER;
    }else{
        free(st);
        return SUCCESS;
    }
}

int stckpt_push(TStckpt *st, point pt){
    if(st == NULL){
        return INVALID_NULL_POINTER;
    }else{
        if(st->qtd == st->max){
            return OUT_OF_MEMORY;
        }
        else{
            st->pt[st->qtd] = pt;
            (st->qtd)++;
            return SUCCESS;
        }
    }
}

int stckpt_pop(TStckpt *st){
    if(st == NULL)
        return INVALID_NULL_POINTER;
    if(st->qtd == 0)
        return EMPTY_LIST;
    else{
        (st->qtd)--;
        return SUCCESS;
    }
}

int stckpt_top(TStckpt *st, point *pt){
    if(st == NULL)
        return INVALID_NULL_POINTER;
    if(st->qtd == 0)
        return EMPTY_LIST;
    else{
        *pt = st->pt[(st->qtd)-1];
        return SUCCESS;
    }
}

int stckpt_empty(TStckpt *st){
    if(st == NULL){
        return INVALID_NULL_POINTER;
    }else{
        if(st->qtd <= 0)
            return EMPTY_LIST;
        else
            return NOT_EMPTY;
    }
}
 
int stckpt_full(TStckpt *st){
    if(st == NULL){
        return INVALID_NULL_POINTER;
    }else{
        if(st->qtd == st->max)
            return FULL_LIST;
        else
            return NOT_FULL;
    }
}

int stckpt_size(TStckpt *st){
    if(st == NULL){
        return INVALID_NULL_POINTER;
    }else{
        return st->qtd;
    }
}