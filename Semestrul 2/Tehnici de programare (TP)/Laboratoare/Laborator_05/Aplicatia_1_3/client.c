#include <stdio.h>
#include <stdlib.h>
#include "hs_utils.h"
#include <time.h>

int main(void)
{
    srand(time(NULL));
    int x1 = rand();
    printf("%d -> palindrom : %d\n",x1, ePalindrom(x1));
    printf("%d -> palindrom : %d\n",12321, ePalindrom(12321));

    printf("Al %d - lea termen Fibbonacci este : %d \n", 10, getFibboTerm(10));

    return 0;
}