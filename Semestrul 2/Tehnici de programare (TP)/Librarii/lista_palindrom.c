// verificati daca o lista simplu inlantuita este sau nu palindrom

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node{
    int value;
    struct node *next;
}Node_t;

typedef Node_t *List_t;

Node_t *makeNode(int value){
    Node_t *newNode = (Node_t *)malloc(sizeof(Node_t));

    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

List_t addFirst(List_t lista, int data){
    Node_t *newNode = makeNode(data);

    if(lista == NULL){
        lista = newNode;
    } else {
        newNode->next = lista;
        lista = newNode;
    }

    return lista;
}

int ePalindrom(List_t lista){
    Node_t *temp = lista;
    int n = 0;
    int i = 0;
    int *v = NULL;

    while(temp != NULL){
        n++;
        v = (int *)realloc(v, n * sizeof(int));
        v[n - 1] = temp->value;
        temp = temp->next;
    }

    for(i = 0; i < n / 2; i++){
        if(v[i] != v[n - i - 1]){
            free(v);
            return 0;
        }
    }

    free(v);
    return 1;
}

void printList(List_t lista){
    Node_t *temp = lista;

    while(temp != NULL){
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}


int main(void){
    srand(time(NULL));

    List_t list = NULL;

    // for(int i = 0; i < 10; i++){
    //     list = addFirst(list, rand() % 100);
    // }

    list = addFirst(list, 1);
    list = addFirst(list, 2);
    list = addFirst(list, 3);
    list = addFirst(list, 2);
    list = addFirst(list, 1);

    printList(list);

    if(ePalindrom(list)){
        printf("Lista este palindrom\n");
    } 
    else {
        printf("Lista nu este palindrom\n");
    }

    return 0;
}