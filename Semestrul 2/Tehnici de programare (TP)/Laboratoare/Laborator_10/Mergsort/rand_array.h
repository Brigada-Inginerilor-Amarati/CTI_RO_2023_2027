#ifndef RAND_ARRAY_H
    #define RAND_ARRAY_H

unsigned* makeRandArray(unsigned seed, unsigned n);

void printArray(unsigned *array, unsigned n);

int* makeRandLimitArray(int seed, unsigned n, int a, int b);

void print_int_array(int *array, unsigned n);

int* makeRandFlexiArray(unsigned n, int (*getNewElem) (int *, unsigned));

int getIncreasingElem(int *array, unsigned n);

int getDecreasingElem(int *array, unsigned n);

int getIncreasing(int *array, unsigned n);

int getDecreasing(int *array, unsigned n);

#endif