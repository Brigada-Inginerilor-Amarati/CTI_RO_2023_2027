#include "lista.h"

struct NODE{
    Element_t value;
    struct NODE *next_nod;
};

Node_t makeNode(Element_t valoare){
    //alocam dinamic si verificam daca a mers
    Node_t nod = malloc(sizeof(struct NODE));

    if(nod == NULL){
        return NULL;
    }

    //umplem campurile
    nod->value = valoare;
    nod->next_nod = NULL;

    return nod;
}

void printList(List_t lista){
    Node_t nod_parcurgere = lista;

    while(nod_parcurgere != NULL){
        printf("%d ", nod_parcurgere->value);
        nod_parcurgere = nod_parcurgere->next_nod;
    }
    printf("\n");
}

void freeList(List_t lista){
    if(lista->next_nod == NULL){
        free(lista);
        return ;
    }

    Node_t nod_de_eliberat = lista;
    lista = lista->next_nod;

    free(nod_de_eliberat);
    return freeList(lista);
}

List_t addFront(List_t lista, Node_t input_nod){
    if (lista == NULL)
    {
        return input_nod;
    }

    input_nod->next_nod = lista; //link la continuarea listei

    lista = input_nod; //actualizam inceputul

    return lista;
    
}

List_t addPosition(List_t lista, Node_t input_node, unsigned int pozitie){
    if(pozitie == 0){
        return addFront(lista, input_node);
    }

    List_t lista_de_parcurs = lista;

    while(pozitie > 1 && lista_de_parcurs->next_nod != NULL){
        pozitie--;
        lista_de_parcurs = lista_de_parcurs->next_nod;
    }

    input_node->next_nod = lista_de_parcurs->next_nod;
    lista_de_parcurs->next_nod = input_node;

    return lista;
}

List_t removeFront(List_t lista){
    Node_t nod_de_sters = lista;

    lista = lista->next_nod;

    free(nod_de_sters);

    return lista;
}

List_t removePosition(List_t lista, unsigned pozitie){
    if(pozitie == 0){
        return removeFront(lista);
    }

    Node_t nod_de_parcurgere = lista;

    while(pozitie > 1 && nod_de_parcurgere->next_nod->next_nod ){ //ai nevoie de 2 noduri in plus, ca sa fii sigur ca nu vei avea null dupa cel sters
        pozitie--;
        nod_de_parcurgere = nod_de_parcurgere->next_nod;
    }

    Node_t nod_de_sters = nod_de_parcurgere->next_nod;
    nod_de_parcurgere->next_nod = nod_de_parcurgere->next_nod->next_nod;
    free(nod_de_sters);

    return lista;
}

// List_t removeNode_value(List_t lista, int valoare){
//     Node_t nod_de_parcurgere = lista;
//     unsigned i = 0;
//     while(nod_de_parcurgere){
//         if(nod_de_parcurgere->value ==  valoare){
//             lista = removePosition(lista, i);
//             i--;
//         }
//         nod_de_parcurgere = nod_de_parcurgere->next_nod;
//         i++;
//     }

//     return lista;
// }

List_t removeNode_value(List_t lista, int valoare) {
    Node_t nod_de_parcurgere = lista;

    while (nod_de_parcurgere != NULL && nod_de_parcurgere->value == valoare) {
        // If the head node is the one to be removed
        Node_t temp = nod_de_parcurgere;
        lista = nod_de_parcurgere->next_nod;
        nod_de_parcurgere = lista;
        free(temp);
    }

    // Now deal with the rest of the list
    while (nod_de_parcurgere != NULL && nod_de_parcurgere->next_nod != NULL) {
        if (nod_de_parcurgere->next_nod->value == valoare) {
            Node_t temp = nod_de_parcurgere->next_nod;
            nod_de_parcurgere->next_nod = nod_de_parcurgere->next_nod->next_nod;
            free(temp);
        } else {
            nod_de_parcurgere = nod_de_parcurgere->next_nod;
        }
    }

    return lista;
}

List_t readFile(char* filepath){
    FILE* input_file = NULL;

    if((input_file = fopen(filepath, "r")) == NULL){
        printf("Nu s-a putut deschide fisierul\n");
        return NULL;
    }

    List_t lista = NULL;
    int x = 0;
    int iterator = 0;

    while(fscanf(input_file, "%d", &x) != EOF){
        lista = addPosition(lista, makeNode(x), iterator);
        iterator++;
    }

    fclose(input_file);
    return lista;
}

void sortare_liste(List_t lista,List_t *l_pare, List_t *l_impare){
    int i = 0;
    int j = 0;
    for(Node_t nod = lista; nod; nod = nod->next_nod){
        if(nod->value % 2 == 0){
            *l_pare = addPosition(*l_pare, makeNode(nod->value), i);
            i++;
        }
        else{
            *l_impare = addPosition(*l_impare, makeNode(nod->value), j);
            j++;
        }
    }
}