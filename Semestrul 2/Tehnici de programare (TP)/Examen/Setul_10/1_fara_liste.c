#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LENGTH 20

void eliminate (int *v, int *n, int B) {
    int newSize = 0;

    for (int i = 0; i < *n; i++)
        if ((B == 1 && i % 2 == 0) || (B == 2 && i % 2 == 1))
            v[newSize ++] = v[i];

    *n = newSize;
}

void print (int* v, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    putchar('\n');
}

int main (void) {
    srand(time(NULL));

    int A[MAX_LENGTH];
    int n = MAX_LENGTH;

    for (int i = 0; i < MAX_LENGTH; i++)
        A[i] = 1 + rand() % 100;
    int B = 1 + rand() % 2;

    print(A, n);
    printf("B = %d\n", B);

    unsigned short iteration = 1;

    while (n > 1) {
        printf("Iteratia %hu: ", iteration ++);
        print(A, n);
        eliminate(A, &n, B);
    }

    printf("Iteratia %hu: ", iteration);
    print(A, n);

    return 0;
}