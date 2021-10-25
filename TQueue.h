#ifndef _tqueueh_
#define _tqueueh_

#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define EMPTY_QUEUE -3
#define NOT_EMPTY -4

typedef struct TQueue TQueue;
typedef struct QNode QNode;

TQueue *queue_create();
int queue_free(TQueue *st);

int queue_push(TQueue *st, char al);
int queue_pop(TQueue *st);
int queue_top(TQueue *st, char *al);

int queue_empty(TQueue *st);

#endif