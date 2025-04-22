// fa un program care sa inverseze o lista

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int value;
    struct node *next_node;
} Node_t;

typedef Node_t* List_t;

Node_t *makeNode(int value) {
    Node_t *newNode = (Node_t *)malloc(sizeof(Node_t));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->value = value;
    newNode->next_node = NULL;

    return newNode;
}

List_t addFirst(List_t lista, int data) {
    Node_t *newNode = makeNode(data);

    if (newNode == NULL) {
        return lista;
    }
    newNode->next_node = lista;
    lista = newNode;

    return newNode;
}

List_t inverseazaLista(List_t lista) {
    List_t inversata = NULL;
    
    while (lista != NULL) {
        Node_t *temp = lista;
        lista = lista->next_node;
        temp->next_node = inversata;
        inversata = temp;
    }
    return inversata;
}

//functie de inversare primelek noduri si pastreaza restul listei asa cum era fara sa o inversezi 1 2 3 4 5 -> primele 3 -> 3 2 1 4 5

List_t inverseazaPrimeleN(List_t lista, int n) {
    if (n <= 0 || lista == NULL) {
        return lista; // nu avem ce inversa sau lista este goala
    }

    List_t inversata = NULL; // lista inversata
    List_t restul = NULL;   // restul listei

    // Inversăm primele n noduri
    int i = 0;
    while (lista != NULL && i < n) {
        Node_t *temp = lista;
        lista = lista->next_node;
        temp->next_node = inversata;
        inversata = temp;
        i++;
    }

    // Adăugăm restul listei nemodificate la sfârșitul listei inversate
    restul = lista; // lista rămasă necompletată

    // Căutăm sfârșitul listei inversate pentru a conecta restul listei la el
    List_t temp = inversata;
    if (temp != NULL) {
        while (temp->next_node != NULL) {
            temp = temp->next_node;
        }
        temp->next_node = restul;
    } else {
        inversata = restul; // dacă nu avem noduri inversate, restul devine lista inversată
    }

    return inversata;
}

void printList(List_t lista) {
    while (lista != NULL) {
        printf("%d ", lista->value);
        lista = lista->next_node;
    }
    printf("\n");
}

int main(void) {
    srand(time(NULL));
    List_t lista = NULL;

    // Adăugăm 10 elemente la listă
    for (int i = 0; i < 10; i++) {
        lista = addFirst(lista, i);
    }

    printf("Lista originală: ");
    printList(lista);

    // lista = inverseazaLista(lista);

    // printf("Lista inversată: ");
    // printList(lista);

    lista = inverseazaPrimeleN(lista, 5);

    printf("Primele 5 elemente inversate: "); 

    printList(lista);


    return 0;
}
