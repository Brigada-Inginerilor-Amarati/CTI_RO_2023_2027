#include <stdlib.h>
#include <stdio.h>
#include "stiva.h"  //pentru fisiere biblioteca definite de utilizator se pune intre " "
#define STIVA_CAP 100

int TEST=555;

struct Stiva{
    Element_t data[STIVA_CAP];
    int head;
};

struct  Stiva st;

void printStatus(){
    printf("TEST ETSE %d\n", TEST);
}


Stiva_t makeStack(){
   Stiva_t st=(Stiva_t)malloc(sizeof(struct Stiva));
   if (st==NULL){
    perror("eroare alocare dinamica stiva");
    return NULL;
   }
   st->head=0;
    return st;
    // st.head=0;
    // return &st;
}

StatusCode_t push(Stiva_t st, Element_t el){
    printf("Inceracare inseare %d cu varf=%d\n", el, st->head);
    if (st!=NULL && st->head<STIVA_CAP){
        st->data[st->head]=el;
        st->head++;
        return STIVA_OK;
    }
    return STIVA_FULL;
}

StatusCode_t peek(Stiva_t st, Element_t* el){
    if (st->head>0){
        *el=st->data[st->head-1];
        return STIVA_OK;
    }
    return STIVA_EMPTY;
}

StatusCode_t pop(Stiva_t st, Element_t* el){
    if (st->head>0){
        st->head--;
        *el=st->data[st->head];
        return STIVA_OK;
    }
    return STIVA_EMPTY;
}

StatusCode_t destroyStack(Stiva_t st){
    free(st);
    return STIVA_OK;
}