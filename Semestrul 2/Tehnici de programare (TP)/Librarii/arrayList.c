// Implementati ArrayList din Java

#include <stdio.h>
#include <stdlib.h>

typedef int Element_t;

typedef struct Node{
    Element_t value;
    struct Node *next_node;
}Node_t;

typedef struct ArrayList{
    Node_t *lista;
    Node_t **array;
    int dimensiune_array;
}ArrayList_t;

Node_t *makeNode(Element_t info){
    Node_t *nod_creat = malloc(sizeof(struct Node));

    if(!nod_creat){
        printf("eroare alocare memorie \n");
        return NULL;
    }

    nod_creat->value = info;
    nod_creat->next_node = NULL;

    return nod_creat;  
}

ArrayList_t *makeArrayList(){
    ArrayList_t *arrayList = malloc(sizeof(struct ArrayList));

    if(!arrayList){
        printf("eroare alocare memorie \n");
        return NULL;
    }

    arrayList->lista = NULL;

    arrayList->array = malloc(sizeof(Node_t*));

    if(!arrayList->array){
        printf("eroare alocare memorie \n");
        free(arrayList);
        return NULL;
    }

    arrayList->dimensiune_array = 0;

    return arrayList;
}

void freeArrayList (ArrayList_t* lista) {
    Node_t* nod = lista->lista;
    Node_t* nod2;
    while (nod->next_node) {
        nod2 = nod;
        free(nod2);
        nod = nod->next_node;
    }

    free(lista->array);
    free(lista);
}

ArrayList_t* updateArray (ArrayList_t* lista) { //  fct asta updateaza de fiecare data vectorul de elemente din arraylist dupa fiecare adaugare / stergere
    Node_t** vector = lista->array;
    if ((vector = realloc(vector, lista->dimensiune_array * sizeof(Node_t*))) == NULL) {
        printf("memorie insuficienta\n");
        freeArrayList(lista);
        return NULL;
    }
    lista->array = vector;
    
    Node_t* nod = lista->lista;
    for (unsigned i = 0; i < lista->dimensiune_array && nod; i ++, nod = nod->next_node)
        lista->array[i] = nod;

    return lista;
}

ArrayList_t *addFront(ArrayList_t *AL, Node_t *nod_de_adaugat){
    if(!AL){
        AL = makeArrayList();
    }

    if(!AL->dimensiune_array){
        AL->lista = nod_de_adaugat; // lista din array incepe cu nodul adaugat
        AL->array[AL->dimensiune_array++] = nod_de_adaugat;

        return AL;
    }

    //asta pt partea de lista
    nod_de_adaugat->next_node = AL->lista;
    AL->lista = nod_de_adaugat;

    //asta pt partea de array
    AL->dimensiune_array++;
    AL = updateArray(AL);

    return AL;
}

ArrayList_t *addPosition(ArrayList_t *AL, Node_t *nod_to_add, int pozitie){
    if(!AL || !pozitie){
        return addFront(AL, nod_to_add);
    }

    if(pozitie >= AL->dimensiune_array){
        return addFront(AL, nod_to_add);
    }

    Node_t *nod = AL->lista;

    while(pozitie > 1 && nod->next_node){
        nod = nod->next_node;
        pozitie--;
    }

    nod_to_add->next_node = nod->next_node;
    nod->next_node = nod_to_add;

    AL->dimensiune_array++;
    AL = updateArray(AL);

    return AL;
}

ArrayList_t *removeFront(ArrayList_t *AL){
    if(!AL){
        printf("arr lista vida \n");
        return NULL;
    }

    if(AL->dimensiune_array){
        Node_t *nod_de_sters = AL->lista;
        AL->lista = AL->lista->next_node;
        free(nod_de_sters);

        AL->dimensiune_array--;
        AL = updateArray(AL);
    }

    return AL;
}

ArrayList_t *removePosition(ArrayList_t *AL, int pozitie){
    if(!AL){
        printf("arr lista vida \n");
        return NULL;
    }

    if(pozitie >= AL->dimensiune_array || pozitie == 0){
        return removeFront(AL);
    }

    Node_t *nod = AL->lista;

    while(pozitie > 1 && nod->next_node){
        nod = nod->next_node;
        pozitie--;
    }

    Node_t *nod_de_sters = nod->next_node;

    nod->next_node = nod->next_node->next_node;

    free(nod_de_sters);

    AL->dimensiune_array--;
    AL = updateArray(AL);

    return AL;
}

void printArrayList(ArrayList_t *AL){
    for(int i = 0; i < AL->dimensiune_array; i++){
        printf("%d ", AL->array[i]->value);
    
    }

    printf("\n");
}

int main(void){
    ArrayList_t *AL = makeArrayList();

    for(int i = 0; i < 10; i ++){
        Node_t *nod = makeNode(i);
        AL = addFront(AL, nod);
    }

    printArrayList(AL);

    for(int i = 0; i < 5; i ++){
        AL = removeFront(AL);
    }

    printArrayList(AL);

    Node_t *nod = makeNode(13);
    AL = addPosition(AL, nod, 2);

    printArrayList(AL);

    AL = removePosition(AL, 2);

    printArrayList(AL);

    freeArrayList(AL);
    return 0;
}