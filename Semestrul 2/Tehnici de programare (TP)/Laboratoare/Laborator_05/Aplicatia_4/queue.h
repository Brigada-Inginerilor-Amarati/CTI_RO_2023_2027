#ifndef __QUEUE_H
#define __QUEUE_H

extern int TEST;
typedef unsigned Element_t;
typedef enum {COADA_OK, COADA_FULL, COADA_EMPTY, COADA_ALLOC_ERR} StatusCode_t;

typedef struct Coada* Coada_t;

Coada_t makeQueue();
StatusCode_t enqueue(Coada_t, Element_t);
StatusCode_t dequeue(Coada_t, Element_t*);
StatusCode_t peekFront(Coada_t, Element_t*);
void printStatus();
StatusCode_t destroyQueue(Coada_t);

#endif
