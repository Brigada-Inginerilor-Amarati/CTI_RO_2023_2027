#ifndef _COADA_
#define _COADA_

typedef struct coada* PQ_T;

typedef enum { OK, Q_FULL } COD;

typedef unsigned el;

PQ_T create(unsigned);

COD insert(PQ_T, el, int(*compare)(void *, void *));

int deque(PQ_T, el *);

void destruct(PQ_T);

#endif