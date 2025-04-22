#include <stdio.h>
#include <stdlib.h>
#include "rand_array.h"
#include <time.h>

int main(void)
{
    //unsigned *array = makeRandArray(10, 10);

    //printArray(array, 10);

    srand(time(NULL));

    int * array_3 = makeRandFlexiArray(10, getIncreasingElem);
    print_int_array(array_3, 10);

    int * array_4 = makeRandFlexiArray(10, getDecreasing);
    print_int_array(array_4, 10);

    //int *int_array = makeRandLimitArray(10, 10, 0, 10);
    //print_int_array(int_array, 10);

    //free(array);
    //free(int_array);
    free(array_3);
    free(array_4);

    return 0;
}