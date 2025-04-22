//stiva cu coada
#include <stdio.h>
#include <stdlib.h>

#define CAP 100

typedef enum Stackcodes{
  Q_OK,
  Q_EMPTY,
  Q_FULL
} OpCode_t;

typedef unsigned Element_t;

typedef struct {
  Element_t* data;
  int cap,tail;
}Queue_t;

Queue_t makeQ(int cap){
  Queue_t q;
  q.tail=0;
  if((q.data=malloc(cap*sizeof(Element_t)))==NULL){
    q.cap=0;
    return q;
  }
  q.cap=cap;
  return q;
}

OpCode_t enqueue(Queue_t *q,Element_t el){
  if(q->tail<q->cap){
    q->data[q->tail]=el;
    q->tail++;
    return Q_OK;
  }
  return Q_FULL;
}

OpCode_t dequeue(Queue_t *q, Element_t *result){
  if(q->tail>0){
    *result=q->data[0];
    for(int i=0;i<q->tail-1;i++){
      q->data[i]=q->data[i+1];
    }
    q->tail--;
    return Q_OK;
  }
  return Q_EMPTY;
}

OpCode_t pop(Queue_t *q,Element_t *result){
  Queue_t aux;
  aux=makeQ(CAP);
  int tail=q->tail;
  Element_t r;
  if(q->tail>0){
    while(q->tail>1){
      dequeue(q,&r);
      //printf("Se scoate - %d\n",r);
      enqueue(&aux,r);
    }
    *result=q->data[q->tail-1];
    while(q->tail<tail){
      dequeue(&aux,&r);
      //printf("Se introduce - %d\n",r);
      enqueue(q,r);
    }
    return Q_OK;
  }
  return Q_EMPTY;
}

int main(void){
  Queue_t st;
  Element_t r;
  OpCode_t status=Q_OK;
  st=makeQ(CAP);
  for(int i=0;i<10;i++){
    enqueue(&st,i);
    printf("Am adaugat %d\n",i);
  }
  for(int i=0;i<5;i++){
    pop(&st,&r);
    printf("Am scos %d\n",r);
  }
  return 0;
}