#ifndef RAND_ARRAY_H
#define RAND_ARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


//proiect 1


unsigned* makeRandArray(unsigned n);

int* makeRandLimitArray(unsigned n, int a, int b);

int* makeRandFlexiArray(unsigned n, int (*getNewElem) (int *, unsigned));

// int getIncreasingElem(int *array, unsigned n);

// int getDecreasingElem(int *array, unsigned n);

int getIncreasing(int *array, unsigned n);

int getDecreasing(int *array, unsigned n);

//proiect 2

double generate_normalDistribution(double media, double abatere);

int generate_poissonDistribution(double lambda);
#endif