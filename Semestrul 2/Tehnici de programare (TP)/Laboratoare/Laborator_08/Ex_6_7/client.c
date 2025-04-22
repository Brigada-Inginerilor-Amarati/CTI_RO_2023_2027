#include "lista.h"

/*
6 Se citesc numere intregi dintr-un fisier text si 

se creeaza o lista cu aceste elemente. Sa se creeze 2 liste care sa 

contina in ordine elementele din fisier, una elementele pare,

 iar cealalta pe cele impare.

7 Sa se creeze o lista liniara simplu inlantuita care

 contine elemente intregi citite dintr-ul fisier text.

Sa se stearga toate nodurile care contin valoarea x.
*/




int main(int argc, char** argv){
    if(argc != 2){
        perror("Nu s-au dat bine argumentele in linie de comanda \n");
        return -1;
    }
    
    List_t lista = readFile(argv[1]);

    if(lista == NULL){
        return -2;
    }
    printList(lista);

    lista = removeNode_value(lista, 3);

    printList(lista);

    //List_t lista_impare = NULL, lista_pare = NULL;

    //sortare_liste(lista, &lista_pare, &lista_impare);

    // printf("pare \n");
    // printList(lista_pare);
    // printList(lista_impare);
     freeList(lista);
    // freeList(lista_pare);
    // freeList(lista_impare);

    return 0;
}