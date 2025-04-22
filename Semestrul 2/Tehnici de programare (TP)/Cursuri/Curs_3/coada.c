#include <stdio.h>
#include <stdlib.h>

#define Q_CAP 10

typedef enum StackCodes{ Q_OK, Q_EMPTY, Q_FULL} OpCode_t;

typedef struct Student{
    char nume[100];
} Student_t;

typedef unsigned Element_t;

typedef struct Queue{
    Element_t* data;
    int cap;
    int tail;
}Queue_t;

Queue_t makeQ(int cap){
    Queue_t q;
    q.tail=0;
    q.data=malloc(cap*sizeof(Element_t));
    if (q.data==NULL){
        q.cap=0;
        return q;
    }
    q.cap=cap;
    return q;
}

OpCode_t enque(Queue_t* q, Element_t el){
    if(q->tail<q->cap){
        q->data[q->tail]=el;
        q->tail++;
        return Q_OK;
    }
    return Q_FULL;
}   

OpCode_t dequeue(Queue_t* q, Element_t* result){
    if(q->tail>0){
        *result=q->data[q->tail-1];
        q->tail--;
        return Q_OK;
    }
    return Q_EMPTY;
}

int main(){

    Queue_t q=makeQ(Q_CAP);
    OpCode_t err;
    for (int i=1; i<=Q_CAP-5; i++){
        if ((err=enque(&q, 100*i))!=Q_OK){
            printf("Eroare la adaugare la pasul %d %d\n", i, err);
        }
        else{
            printf("Ok la %d\n", i);
        }
    }
    Element_t value;
    for (int i=1; i<=7; i++){
        if ((err=dequeue(&q, &value))==Q_OK){
            printf("Am reusit sa scor %u\n", value);
        }
        else{
            printf("A aparut eroarea %d\n", err);
        }
    }
   
    return 0;
}