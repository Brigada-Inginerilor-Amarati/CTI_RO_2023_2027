/*
1. Sa se implementeze o functie C care primeste un numar natural n,

construieste si afiseaza un șir format din primele 2^n numere naturale, dispuse astfel:

    se pleacă de la șirul 1 2

    exact la mijlocul acestui șir se inserează șirul 3 4 și se obține 1 3 4 2

    exact la mijlocul acestui șir se inserează șirul 5 6 7 8 și se obține 1 3 5 6 7 8 4 2

    etc
    în general, la mijlocul șirului format din primele 2^k numere naturale se inserează 
    
    șirul ordonat format din următoarele 2^k numere naturale.

Se va implemente o functie main() adecvata si orice alte functii necesare.
*/

#include <stdio.h>
#include <stdlib.h>

void insert_middle(int* array, int size, int* new_elements, int new_size) {
    int total_size = size + new_size;
    int mid = size / 2;
    
    // Shift elements to the right to make space for new elements
    for (int i = size - 1; i >= mid; i--) {
        array[i + new_size] = array[i];
    }

    // Insert new elements in the middle
    for (int i = 0; i < new_size; i++) {
        array[mid + i] = new_elements[i];
    }
}

void construct_and_display_series(int n) {
    int total_elements = 1 << n; // 2^n
    int* series = (int*)malloc(total_elements * sizeof(int));
    if (!series) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // Initial series with first 2 elements
    series[0] = 1;
    series[1] = 2;
    int current_size = 2;

    for (int i = 1; i < n; i++) {
        int new_size = 1 << i; // 2^i
        int* new_elements = (int*)malloc(new_size * sizeof(int));
        if (!new_elements) {
            fprintf(stderr, "Memory allocation failed\n");
            free(series);
            return;
        }

        // Fill new elements
        for (int j = 0; j < new_size; j++) {
            new_elements[j] = current_size + 1 + j;
        }

        // Insert new elements in the middle of the series
        insert_middle(series, current_size, new_elements, new_size);
        current_size += new_size;

        free(new_elements);
    }

    // Display the series
    for (int i = 0; i < total_elements; i++) {
        printf("%d ", series[i]);
    }
    printf("\n");

    free(series);
}

int main() {
    int n;
    printf("Introduceti un numar natural n: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("n trebuie sa fie cel putin 1\n");
        return 1;
    }

    construct_and_display_series(n);
    return 0;
}