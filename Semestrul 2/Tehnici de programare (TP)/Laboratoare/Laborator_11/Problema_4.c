/*
4. Se dă un șir de n numere naturale. 

Șirul poate fi partiționat în mai multe moduri într-un număr

de subșiruri strict crescătoare. De exemplu, șirul 4 6 2 5 8 1 3 7 
 
poate fi partiționat astfel: 4 6 8 (primul subșir), 2 5 7 (al doilea) 
 
și 1 3 (al treilea). O altă modalitate este formând
 
patru subșiruri: 4 5 7, 6 8, 2 3 și 1.

*/



#include <stdio.h>
#include <stdlib.h>

void print_partition(int *partition, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", partition[i]);
    }
    printf("\n");
}

int main(void){
    int n = 8;
    int v[] = {4, 6, 2, 5, 8, 1, 3, 7};

    //n = sizeof(v) / sizeof(v[0]);

    int *used = calloc(n, sizeof(int));

    int *partition = malloc(n * sizeof(int));

    int index;

for (int i = 0; i < n; i++) {
        if (used[i] == 1) {
            continue;
        }
        partition[0] = v[i];
        int index = 1;
        used[i] = 1;

        int last_value = partition[0];

        for (int j = i + 1; j < n; j++) {
            if (!used[j] && v[j] > last_value) {
                partition[index++] = v[j];
                used[j] = 1;
                last_value = v[j];  // Update last_value
            }
        }

        print_partition(partition, index);
    }

    free(used);
    free(partition);
    return 0;
}