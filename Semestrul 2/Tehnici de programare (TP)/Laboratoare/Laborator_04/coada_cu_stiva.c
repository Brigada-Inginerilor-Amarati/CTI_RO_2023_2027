//coada cu stiva
#include <stdio.h>
#include <stdlib.h>

#define CAP 100

typedef enum StackCodes{ ST_OK, ST_EMPTY, ST_FULL} OpCode_t;

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

Stack_t enqueue(Stack_t st, Element_t el,OpCode_t *status){
    if (st.sp<st.cap){
        st.data[st.sp]=el;
        st.sp++;
	*status=ST_OK;
    }
    else{
      *status=ST_FULL;
    }
    return st;
}

Stack_t push(Stack_t st, Element_t el,OpCode_t *status){
    if (st.sp<st.cap){
        st.data[st.sp]=el;
        st.sp++;
	*status=ST_OK;
    }
    else{
      *status=ST_FULL;
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
    if (*status==ST_OK){
        st->sp--;
    }
    return aux;
}

Element_t dequeue(Stack_t* st,OpCode_t* status_dequeue){
  Stack_t aux;
  aux=makeStack(CAP);
  OpCode_t status;
  Element_t elem=0,first=0;
  if(st->sp >0 ){
    status=ST_OK;
    while(st->sp>0 && status==ST_OK){
      elem=pop(st,&status);
      aux=push(aux,elem,&status);
    }
    first=pop(&aux,&status);
    while(aux.sp>0){
      elem=pop(&aux,&status);
      *st=push(*st,elem,&status);
    }
    *status_dequeue=status;
    return first;
  }
  *status_dequeue=ST_EMPTY;
  return 0;
}

int main(void){
  Stack_t queue;
  OpCode_t status;
  Element_t elem=0;
  queue=makeStack(CAP);
  for(int i=0;i<20;i++){
    queue=enqueue(queue,i*10,&status);
    if(status==ST_OK){
      printf("Am adaugat %d\n",i*10);
    }
  }
  for(int i=0;i<10;i++){
    elem = dequeue(&queue,&status);
      if(status==ST_OK){
	printf("Am scos %d\n",elem);
      }
      if(status==ST_EMPTY){
	printf("Este goala\n");
      }
  }
  elem=peek(queue,&status);
  printf("peek-ul este %d\n",elem);
  return 0;
}