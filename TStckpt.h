#ifndef _TStckpth_
#define _TStckpth_

#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -3
#define ELEM_NOT_FOUND -4
#define EMPTY_LIST -5
#define FULL_LIST -6
#define NOT_EMPTY -7
#define NOT_FULL -8

struct point{
    int i;
    int j;
};

typedef struct TStckpt TStckpt;
typedef struct point point;

TStckpt *stckpt_create();
int stckpt_free(TStckpt *st);
int stckpt_push(TStckpt *st, point pt);
int stckpt_pop(TStckpt *st);
int stckpt_top(TStckpt *st, point *pt);

int stckpt_empty(TStckpt *st); 
int stckpt_full(TStckpt *st);
int stckpt_print(TStckpt *st);
int stckpt_size(TStckpt *st);

#endif