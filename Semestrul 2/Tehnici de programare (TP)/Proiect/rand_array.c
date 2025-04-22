#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "rand_array.h"


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif



/*
1. Implementati o functie unsigned* makeRandArray(unsigned seed, unsigned n), care primeste un seed 

si un numar natural n si

 returneaza un vector alocat dinamic, continand n numere naturale pseodoaleatoare, uniform distribuite
*/

//am sters seed pt ca altfel mi-ar fi generat aceleasi nr de fiecare data
unsigned* makeRandArray(unsigned n)
{
    unsigned *array = (unsigned*) malloc(n * sizeof(unsigned));

    if(array == NULL)
    {
        perror("Nu s-a putut aloca memorie\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < n; i++)
    {
        array[i] = rand();
    }

    return array;
}

/*
2. Implementati o functie int* makeRandLimitArray(int seed, unsigned n, int a, int b) 

care primeste un seed, si numerele naturale n, a si b si returneaza un vector alocat dinamic, 

continand n numere intregi pseudoaleatoare, uniform distribuite, cuprinse intre a si b
*/


//am scos seed ul din acelasi motiv ca si sus

int* makeRandLimitArray(unsigned n, int a, int b)
{
    int* array = (int*) malloc(n * sizeof(int));

    if(array == NULL)
    {
        perror("Nu s-a putut aloca memorie. \n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < n; i++)
    {
        array[i] = a + rand() % (b - a + 1);
    }

    return array;
}

/*
3. Implementati o functie cu antetul int* makeRandFlexiArray(unsigned n, int (*getNewElem)(int*, unsigned)) 

care genereaza un vector alocat dinamic cuprinzand elemente numere psoedoaleatoare. 

Pentru generarea unui nou element din vector se va face apel la o functie "concreta" primita 

sub forma unui pointer la o functie care primeste drept argumente un tablou si numarul 

sau curent de elemente. Implementati functii "concrete" 

pentru generarea unor vectori monoton crescatori si monoton descrescatori.
*/

int *makeRandFlexiArray(unsigned n, int (*getNewElem)(int*, unsigned))
{
    int *array = (int *) malloc(n * sizeof(int));

    if(array == NULL)
    {
        perror("Nu s-a putu aloca memorie. \n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < n; i++)
    {
        array[i] = getNewElem(array, i);
    }

    return array;
}

// int getIncreasingElem(int *array, unsigned n)
// {
//     return n == 0 ? 0 : array[n-1] + 1;
// }

// int getDecreasingElem(int *array, unsigned n)
// {
//     return n == 0 ? 0 : array[n-1] - 1;
// }

// PROIECT 2 -- Distributia normala

double generate_normalDistribution(double media, double abatere)
{
    double u1 = (double) rand() / RAND_MAX;
    double u2 = (double) rand() / RAND_MAX;

    double z = sqrt(-2  * log(u1)) * cos(2 * M_PI * u2);

    return media + z * abatere;
}

// Distributia Poisson

int generate_poissonDistribution(double lambda)
{
    double limit = exp(-lambda);
    double p = (double) rand() / RAND_MAX;
    int n = 0;

    for(n = 0; p >= limit; n++){
        p = p * (double) rand() / RAND_MAX;
    }

    return n;
}