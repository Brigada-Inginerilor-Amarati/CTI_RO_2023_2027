// fa un program care sa ilustreze functionalitatea unei double  ended queue 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int *data;
    int head;
    int tail;
    int stare;
    int capacity;
    int current_size;
}deque_t;

deque_t *makeDeque(int cap){
    deque_t *deque = malloc(sizeof(deque_t));

    if(!deque){
        printf("Eroare memorie \n");
        return NULL;
    }

    deque->data = malloc(cap * sizeof(int));
    if(!deque->data){
        printf("Eroare memorie vector\n");
        free(deque);
        return NULL;
    }

    deque->head = 0;
    deque->tail = 0;
    deque->stare = 0;
    deque->capacity = cap;
    deque->current_size = 0;

    return deque;
}

deque_t *pushFront(deque_t *deque, int data){
    if(deque->current_size < deque->capacity){
        deque->data[deque->tail] = data;
        deque->tail++;
        deque->stare = 1;
        deque->current_size++;
    }
    else{
        printf("Deque plin\n");
    }

    return deque;
}

deque_t *pushBack(deque_t *deque, int data){
    if(deque->tail < deque->capacity){
        deque->data[deque->tail] = data;
        deque->tail++;
        deque->stare = 1;
        deque->current_size++;

    }
    else{
        printf("Deque plin\n");
    }

    return deque;
}




void printDeque(deque_t *deque){
    if(deque->stare == 0){
        printf("Deque gol\n");
        return;
    }

    for(int i = deque->head; i < deque->tail; i++){
        printf("%d ", deque->data[i]);
    }
    printf("\n");

}

int main(void){
    srand(time(NULL));

    deque_t *deque = makeDeque(10);

    if(!deque){
        return -1;
    }

    //adaugam in coada nr
    for(int i = 0; i < 8; i++){
        deque = pushFront(deque, i);
        // deque = pushFront(deque, rand() % 100);
    }

    deque = pushBack(deque, 10);

    printDeque(deque);

    free(deque->data);
    free(deque);

    return 0;
}

/*
varianta cu lista 
#include <stdio.h>
#include <stdlib.h>

// Node structure for a doubly linked list
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Deque structure
typedef struct {
    Node* front;
    Node* rear;
} Deque;

// Function to create a new node
Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = temp->prev = NULL;
    return temp;
}

// Initialize the deque
void initDeque(Deque* dq) {
    dq->front = dq->rear = NULL;
}

// Check if deque is empty
int isEmpty(Deque* dq) {
    return (dq->front == NULL);
}

// Insert at front
void insertFront(Deque* dq, int data) {
    Node* temp = newNode(data);
    if (isEmpty(dq)) {
        dq->front = dq->rear = temp;
    } else {
        temp->next = dq->front;
        dq->front->prev = temp;
        dq->front = temp;
    }
}

// Insert at rear
void insertRear(Deque* dq, int data) {
    Node* temp = newNode(data);
    if (isEmpty(dq)) {
        dq->front = dq->rear = temp;
    } else {
        temp->prev = dq->rear;
        dq->rear->next = temp;
        dq->rear = temp;
    }
}

// Delete from front
int deleteFront(Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty\n");
        return -1;
    }
    Node* temp = dq->front;
    int data = temp->data;
    dq->front = dq->front->next;
    if (dq->front == NULL) {
        dq->rear = NULL;
    } else {
        dq->front->prev = NULL;
    }
    free(temp);
    return data;
}

// Delete from rear
int deleteRear(Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty\n");
        return -1;
    }
    Node* temp = dq->rear;
    int data = temp->data;
    dq->rear = dq->rear->prev;
    if (dq->rear == NULL) {
        dq->front = NULL;
    } else {
        dq->rear->next = NULL;
    }
    free(temp);
    return data;
}

// Display the deque
void displayDeque(Deque* dq) {
    Node* temp = dq->front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Deque dq;
    initDeque(&dq);

    insertFront(&dq, 10);
    insertRear(&dq, 20);
    insertFront(&dq, 5);
    insertRear(&dq, 25);

    printf("Deque after inserts: ");
    displayDeque(&dq);

    printf("Deleted from front: %d\n", deleteFront(&dq));
    printf("Deleted from rear: %d\n", deleteRear(&dq));

    printf("Deque after deletions: ");
    displayDeque(&dq);

    return 0;
}

*/
