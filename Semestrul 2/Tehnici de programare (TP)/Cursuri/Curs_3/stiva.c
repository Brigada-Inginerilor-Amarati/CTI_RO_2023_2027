#include <stdio.h>
#include <stdlib.h>

typedef enum StackCodes{ ST_OK, ST_EMPTY, ST_FULL} OpCode_t;

typedef struct Student{
    char nume[100];
} Student_t;

typedef unsigned Element_t;

typedef struct Stack{
    unsigned sp;
    unsigned cap;
    Element_t* data;
} Stack_t;

Stack_t makeStack(unsigned cap){
    Stack_t st;
    st.sp=0;
    st.data=malloc(cap*sizeof(Element_t));
    if (st.data==NULL){
        st.cap=0;
        return st;
    }
    st.cap=cap;
    return st;
}

Stack_t push(Stack_t st, Element_t el){
    if (st.sp<st.cap){
        st.data[st.sp]=el;
        st.sp++;
    }
    return st;
}

Element_t peek(Stack_t st, OpCode_t* c){
    if (st.sp>0){
        *c=ST_OK;
        return st.data[st.sp-1];
    }
    else{
        *c=ST_EMPTY;
        return 0;
    }
}

Element_t pop(Stack_t* st, OpCode_t* status){
    
    Element_t aux=peek(*st, status);
    if (*status==ST_OK)
        st->sp--;
    return aux;
}

int main(){

    Stack_t st=makeStack(10);
    
    OpCode_t status;
     Element_t aux=peek(st, &status);
    // if (status==ST_OK)printf ("Dupa 30 avem %u\n", aux);//30
    // else{
    //     printf("eraore la stiva %d\n", status);
    // }
    st=push(st, 10);
    st=push(st, 20);
    st=push(st, 30);
    
    aux=peek(st, &status);
    if (status==ST_OK)printf ("Dupa 30 avem %u\n", aux);//30
    else{
        printf("eraore la stiva %d\n", status);
    }
    
    Element_t vf=pop(&st, &status);
    if (status==ST_OK){
        printf("Elementul din var este %u\n", vf );
    }

    aux=peek(st, &status);
    if (status==ST_OK)printf ("Dupa ce am scos varful 30 avem %u\n", aux);//20
    else{
        printf("eraore la stiva %d\n", status);
    }

    //printf("Dupa 50 avem %u\n", peek(st));//50
    return 0;
}