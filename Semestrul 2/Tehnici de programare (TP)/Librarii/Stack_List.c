// implementatii stiva cu o lista

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int data;
    int priority;
    struct node *next_node;
} Node_t;

typedef struct stack{
    Node_t *top;
    int size;
}Stack_t;

//INIT

Node_t *makeNode(int data, int priority){
    Node_t *nod_creat = malloc(sizeof(Node_t));

    if(!nod_creat){
        return NULL;
    }

    (*nod_creat) = (struct node) {data, priority, NULL};
    return nod_creat;
}

Stack_t *initStack(){
    Stack_t *stiva = malloc(sizeof(Stack_t));

    if(!stiva){
        return NULL;
    }

    (*stiva) = (struct stack) {NULL, 0};

    return stiva;
}


//PUSH

Stack_t *pushFirst(Stack_t *stiva, Node_t *nod_to_add){
    stiva->size++;

    if(stiva->size == 1){
        stiva->top = nod_to_add;
        return stiva;
    }

    nod_to_add->next_node = stiva->top;
    stiva->top = nod_to_add;

    return stiva;
}

int priorityCheck(Node_t *main, Node_t *comparator){ //main este nodul 
    return main->priority < comparator->priority;

}

Stack_t *pushPriority(Stack_t *stiva, Node_t *nod_to_add){
    stiva->size++;

    if(stiva->size == 1){
        stiva->top = nod_to_add;
        return stiva;
    }

    //prioritar
    if(priorityCheck(nod_to_add, stiva->top)){
        nod_to_add->next_node = stiva->top;
        stiva->top = nod_to_add;

        return stiva;
    }

    Node_t *prev_node = stiva->top;
    Node_t *current_node = stiva->top->next_node;

    while(current_node){
        if(priorityCheck(nod_to_add, current_node)){
            nod_to_add->next_node = current_node;
            prev_node->next_node = nod_to_add;

            return stiva;
        }

        prev_node = prev_node->next_node;
        current_node = current_node->next_node;
    }

    prev_node->next_node = nod_to_add;

    return stiva;
}

//REMOVE

Stack_t *pop(Stack_t *stiva){
    if(stiva->size == 0){
        return stiva;
    }

    if(stiva->size == 1){
        stiva->size = 0;
        free(stiva->top);
        return stiva;
    }

    stiva->size --;

    Node_t *temp = stiva->top;
    stiva->top = stiva->top->next_node;

    free(temp);
    return stiva;
}


//PRINT

void printStack(Stack_t *stiva){
    if(stiva->size == 0){
        printf("Stiva este goala\n");
        return;
    }

    Node_t *nod_curent = stiva->top;

    while(nod_curent){
        printf("Data: %d, Prioritate: %d\n", nod_curent->data, nod_curent->priority);
        nod_curent = nod_curent->next_node;
    }
}



//FREE

void freeStack(Stack_t *stiva){
    Node_t *nod_curent = NULL;

    for(int i = 0; i < stiva->size; i++){
        nod_curent = stiva->top;
        stiva->top = stiva->top->next_node;
        free(nod_curent);
    }

    free(stiva);
}

//MAIN

int main(void){
    srand(time(NULL));
    int size = 2 + rand() % 5;
    Stack_t *stiva = initStack();

    for(int i = 0; i < size; i++){
        Node_t *nod = makeNode(rand() % 100, rand() % 100);
        stiva = pushPriority(stiva, nod);
    }

    printStack(stiva);

    printf("----------------------\n");
    //add without priority
    Node_t *nod = makeNode(100, 100);
    stiva = pushFirst(stiva, nod);
    printStack(stiva);

    printf("----------------------\n");
    //remove
    stiva = pop(stiva);
    printStack(stiva);  
    

    freeStack(stiva);


    return 0;
}