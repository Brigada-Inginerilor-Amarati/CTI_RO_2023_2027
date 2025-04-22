#ifndef __AVION_H
    #define __AVION_H

typedef struct Pasager Pasager_t;

typedef struct Avion Avion_t;

Avion_t* makeAvion(unsigned int nr_locuri_categoria_1, unsigned int nr_locuri_categoria_3);

Avion_t* adaugare(Avion_t* a, char* nume, int gr_b, int nr_cat); 

//primeste drept parametru un pointer la un Avion_t curent si 

//parametrii specifici unui Pasager_t. Functia adauga pasagerul 

//nou creat la categoria de locuri corespunzatoare DOAR daca mai exista 

//locuri disponibile la acea categorie. In caz contrar, se va returna avionul

// nemodificat si se va afisa mesajul “Nu mai sunt locuri la categoria x” 

//(x poate fi 1 sau 2).

int compararePasageri(const void *a, const void *b);

void afisarePasageri(Avion_t *, int g);
// va afisa in ordine alfabetica datele pasagerilor din avion care au 

//greutatea mai mare decat g

int mutarePasageri(Avion_t*, int x, int nr_cat); //ultimii x pasageri din categoria nr_cat trebuie mutati in cealalta categorie.

// Functia returneaza numarul de pasageri care au putut fi mutati tinandu-se cont de numarul de locuri disponibile

#endif