#include <stdio.h>
#include <stdlib.h>
#include "avion.h"

int main(void)
{
    Avion_t *avion1 = makeAvion(10, 10);

    
    avion1 = adaugare(avion1, "Daria", 3, 1);

    avion1 = adaugare(avion1, "Anisia", 10, 1);

    avion1 = adaugare(avion1, "Dan", 13, 2);
    //avion1 = adaugare(avion1, "Ileana", 13, 2);
    printf("Pasageri inainte de mutare: \n");
    afisarePasageri(avion1, 0);

    printf("Pasageri dupa o mutare: \n");
    mutarePasageri(avion1, 1, 2);
    afisarePasageri(avion1, 5);

    printf("Pasageri dupa 2 mutari: \n");
    mutarePasageri(avion1, 2, 1);

    afisarePasageri(avion1, 0);

    return 0;
}