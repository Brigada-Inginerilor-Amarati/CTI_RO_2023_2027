#ifndef __MATRICE_H
#define __MATRICE_H

typedef enum {OK, EROARE_DEPASIRE_LIMITE} StatusCode_t;

typedef int Element_t;

typedef struct  Matrice* Tab2D_t;

typedef struct Vector* Vector_t;

Tab2D_t creeaza_tablou(unsigned int nr_linii, unsigned int nr_coloane);

StatusCode_t atribuie_valoare(Tab2D_t, unsigned int, unsigned int, Element_t);

void afiseaza_matrice(Tab2D_t Matrice);

Tab2D_t insumeaza_matrici(Tab2D_t, Tab2D_t);

Vector_t initializeaza_vector(unsigned int dimensiune);

void afiseaza_vector(Vector_t vector);

Vector_t copiaza(Tab2D_t matrice, int(*cond)(Element_t));

int este_impar(Element_t);

#endif