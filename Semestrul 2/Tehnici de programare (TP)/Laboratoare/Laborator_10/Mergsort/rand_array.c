#include <stdlib.h>
#include <stdio.h>
#include "rand_array.h"

void printArray(unsigned *array, unsigned n)
{
    for(size_t i = 0; i < n; i++)
    {
        printf("v[%ld] = %u \n", i, array[i]);
    }

    printf("\n");
}

/*
1. Implementati o functie unsigned* makeRandArray(unsigned seed, unsigned n), care primeste un seed 

si un numar natural n si

 returneaza un vector alocat dinamic, continand n numere naturale pseodoaleatoare, uniform distribuite
*/

unsigned* makeRandArray(unsigned seed, unsigned n)
{
    unsigned *array = (unsigned*) malloc(n * sizeof(unsigned));

    if(array == NULL)
    {
        perror("Nu s-a putut aloca memorie\n");
        exit(EXIT_FAILURE);
    }

    srand(seed);
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

void print_int_array(int *array, unsigned n)
{
    for(size_t i = 0; i < n; i++)
    {
        printf("v[%ld] = %d \n", i, array[i]);
    }

    printf("\n");
}

int* makeRandLimitArray(int seed, unsigned n, int a, int b)
{
    int* array = (int*) malloc(n * sizeof(int));

    if(array == NULL)
    {
        perror("Nu s-a putut aloca memorie. \n");
        exit(EXIT_FAILURE);
    }

    srand(seed);

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

int getIncreasingElem(int *array, unsigned n)
{
    return n == 0 ? 0 : array[n-1] + 1;
}

int getDecreasingElem(int *array, unsigned n)
{
    return n == 0 ? 0 : array[n-1] - 1;
}

int getIncreasing(int *array, unsigned n)
{
    if(n == 0)
    {
        return rand()% 10;
    }

    return array[n-1] + rand() % 2;
}

int getDecreasing(int *array, unsigned n)
{
    if(n == 0)
    {
        return rand();
    }

    return array[n-1] - rand() % 1000;
}
