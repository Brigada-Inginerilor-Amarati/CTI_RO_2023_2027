#include <stdio.h>
#include "film.h"
#include <time.h>

int main (void) {
    Site_t site = NULL;

    char nume[13];
    srand(time(NULL));
    for(int i = 0; i < 12; i++){
        nume[i] = 'a' + rand()%26;
    }
    nume[12] = 0;


    site = adaugare(site, nume, "actiune, comedie", 2, 90);
    site = adaugare(site, "film3", "romance, comedie", 30, 150);
    site = adaugare(site, "film2", "romance, comedie", 20, 250);
    site = adaugare(site, "film4", "thriller, comedie",10, 150);
    afisareFilme(site);

    afisareMaxim(site);
    return 0;
}