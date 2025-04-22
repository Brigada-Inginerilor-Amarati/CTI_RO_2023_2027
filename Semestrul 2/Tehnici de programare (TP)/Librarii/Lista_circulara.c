// Creati un program care arata cum functioneaza o lista circulara
// in care putem adauga elemente la inceputul listei si la sfarsitul listei
// si putem sterge elemente de la inceputul listei si de la sfarsitul listei
// si putem afisa elementele listei

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define a structure for the nodes of the linked list
typedef struct Node{
    int value;
    struct Node* nod_urmator;
}Node_t;

typedef Node_t * List_t;

// Function to create a new node
Node_t *makeNode(int data){
    Node_t *nod_creat = malloc(sizeof(struct Node));

    //va trb verificat cazul de NULL in main
    if(!nod_creat){
        printf("eroare la alocarea memoriei\n");
        return NULL;
    }

    nod_creat->value = data;
    nod_creat->nod_urmator = NULL;

    return nod_creat;
}

// functie ca sa adaugam un nod in lista circulara la inceput

List_t addFirst(List_t lista, int data){
    Node_t *nod_de_adaugat = makeNode(data);

    //caz de tratat in main
    if(!nod_de_adaugat){
        return NULL;
    }

    if(!lista){
        nod_de_adaugat->nod_urmator = nod_de_adaugat;
        return nod_de_adaugat;
    }
    Node_t *aux = lista;

    while (aux->nod_urmator != lista)
    {
        aux = aux->nod_urmator;
    }

    aux->nod_urmator = nod_de_adaugat;
    nod_de_adaugat->nod_urmator = lista;
    //fara asta nu vom updata capul listei
    lista = nod_de_adaugat;
    
    return lista;
}

//functie de adaugare la final

List_t addLast(List_t lista, int data){
    Node_t *nod_de_adaugat = makeNode(data);

    if(!nod_de_adaugat){
        return NULL;
    }

    if(!lista){
        nod_de_adaugat->nod_urmator = nod_de_adaugat;
        return nod_de_adaugat;
    }

    Node_t *aux = lista;

    while(aux->nod_urmator->nod_urmator != lista){
        aux = aux->nod_urmator;
    }

    aux->nod_urmator->nod_urmator = nod_de_adaugat;
    nod_de_adaugat->nod_urmator = lista;

    return lista;
}

//functie de adagare dupa index

List_t addIndex(List_t lista, int data, int pozitie){
    Node_t *nod_deadaugat = makeNode(data);

    if(!nod_deadaugat){
        return NULL;
    }

    if(!lista){
        nod_deadaugat->nod_urmator = nod_deadaugat;
        return nod_deadaugat;
    }

    Node_t *aux = lista;

    while(pozitie > 1){
        aux = aux->nod_urmator;
        pozitie--;
    }

    nod_deadaugat->nod_urmator = aux->nod_urmator;
    aux->nod_urmator = nod_deadaugat;

    return lista;
}

//functie de stergere de la inceput

List_t deleteFirst(List_t lista){
    if(!lista){
        printf("Lista este goala\n");
        return NULL;
    }
    //la asta va trb sa  dam free;
    Node_t *temp = lista;
    //lista = lista->nod_urmator; //suntem din nodul 0 la nodul 1

    Node_t *aux = lista;
    while (aux->nod_urmator != lista)
    {
        aux = aux->nod_urmator;
    }

    //acum ne aflam la ultimul nod

    aux->nod_urmator = lista->nod_urmator;
    lista = lista->nod_urmator;

    free(temp);
    
    return lista;
}

// Function to delete the last node of the circular linked list
List_t deleteLast(List_t lista){
    if(!lista){
        printf("Lista este goala\n");
        return NULL;
    }
    
    Node_t *aux = lista;

    while (aux->nod_urmator->nod_urmator != lista){
        aux = aux->nod_urmator;
    }

    Node_t *temp = aux->nod_urmator;

    aux->nod_urmator = lista;

    free(temp);

    return lista;
}

// Function to delete a node at a given index in the circular linked list
List_t deleteIndex(List_t lista, int index){
    if(!lista){
        printf("Lista este goala\n");
        return NULL;
    }

    Node_t *aux = lista;

    while (index > 1)
    {
        aux = aux->nod_urmator;
        index--;
    }

    Node_t *temp = aux->nod_urmator;

    aux->nod_urmator = aux->nod_urmator->nod_urmator;

    free(temp);
    
    return lista;
}

// Function to print the elements of the circular linked list
void printLista(List_t lista){
    if(!lista){
        printf("Lista este goala\n");
        return;
    }

    Node_t *aux = lista;

    do{
        printf("%d ", aux->value);
        aux = aux->nod_urmator;
    }while(aux != lista);

    printf("\n");
}


int main(void){
    srand(time(NULL));

    List_t lista = NULL;

    int size = 9;//= rand() % 10 + 1;

    //printf("Dimensiunea listei este %d \n", size);

    for(int i = 0; i < size; i++){
        lista = addFirst(lista, i);
    }

    lista = addLast(lista, size);

    lista = addIndex(lista, 13, 2);

    lista = deleteFirst(lista);

    printLista(lista);

    lista = deleteLast(lista);

    lista = deleteIndex(lista, 1);

    printLista(lista);

    return 0;
}