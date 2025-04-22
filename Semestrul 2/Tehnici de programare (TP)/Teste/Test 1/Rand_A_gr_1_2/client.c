#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"

int main(void)
{
    Tab2D_t matrice1 = creeaza_tablou(3,3);
    Tab2D_t matrice2 = creeaza_tablou(3,3);

    
    atribuie_valoare(matrice1, 0, 0, 3);
    atribuie_valoare(matrice1, 2, 2, 3);
    atribuie_valoare(matrice1, 1, 2, 7);
    atribuie_valoare(matrice1, 2, 1, 9);
    atribuie_valoare(matrice1, 1, 1, 2);
    afiseaza_matrice(matrice1);

    atribuie_valoare(matrice2, 0, 0, 3);

    afiseaza_matrice(matrice2);

    Tab2D_t matrice_suma = insumeaza_matrici(matrice1, matrice2);

    afiseaza_matrice(matrice_suma);

    Vector_t vector = initializeaza_vector(9);

    vector = copiaza(matrice1, este_impar);
    printf("\nVectorul este : ");
    afiseaza_vector(vector);
    return 0;
}