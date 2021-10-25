#include <stdlib.h>
#include "TStack.h"

struct TStack{
    int max;
    int qtd;
    char *data;
};

TStack *stack_create(){
    TStack *st;
    st = malloc(sizeof(TStack));
    if (st != NULL){
        st->qtd = 0;
        st->max = 100;
        st->data = (char *)malloc(st->max*sizeof(char));
        if (st->data == NULL){
            free(st);
            return OUT_OF_MEMORY;
        }
    return st;
    }else{
        return INVALID_NULL_POINTER;
    }
}

int stack_free(TStack *st){
    if(st == NULL){
        return INVALID_NULL_POINTER;
    }else{
        free(st);
        return SUCCESS;
    }
}

int stack_push(TStack *st, char ch){
    if(st == NULL){
        return INVALID_NULL_POINTER;
    }else{
        if(st->qtd == st->max){
            return OUT_OF_MEMORY;
        }
        else{
            st->data[st->qtd] = ch;
            (st->qtd)++;
            return SUCCESS;
        }
    }
}

int stack_pop(TStack *st){
    if(st == NULL){
        return INVALID_NULL_POINTER;
    }else{
        (st->qtd)--;
        return SUCCESS;
    }
}

int stack_top(TStack *st, char *ch){
    if(st == NULL){
        return INVALID_NULL_POINTER;
    }else{
        *ch = st->data[(st->qtd)-1];
        return SUCCESS;
    }
}

int stack_empty(TStack *st){
    if(st == NULL){
        return INVALID_NULL_POINTER;
    }else{
        if(st->qtd > 0)
            return SUCCESS;
        else
            return NOT_EMPTY;
    }
}

int stack_full(TStack *st){
    if(st == NULL){
        return INVALID_NULL_POINTER;
    }else{
        if(st->qtd == st->max)
            return FULL_LIST;
        else
            return NOT_FULL;
    }
}