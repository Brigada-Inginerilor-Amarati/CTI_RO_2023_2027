/*
o tabla de sah de tip n, m, k

n linii, m coloane cu elemente {0, 1}

grupate in patrate k * k

Mereu matricea incepe cu grupare de 0

Construiti o astfel de tabla
*/

#include <stdio.h>
#include <stdlib.h>

int matrix[100][100];

void patrate(int n, int m, int k, int element){

    for(int i = 0; i < k; i++){

        for(int j = 0; j < k; j++){

            matrix[n + i][m + j] = element;
        }
    }
}

void print(int n, int m){
    for(int i = 0; i < n; i++){

        for(int j = 0; j < m; j++){

            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void fa_matricea(int n, int m, int k){
    int element = 0;
    for(int i = 0; i < n; i+= k){

        for(int j = 0; j < m; j+=k){
            patrate(i, j, k, element);
            element = !element;
        }

        if (m % (2 * k) == 0)
        {
            element = !element;
        }
        
    }
}

int main(void){
    int n = 6;
    int m = 6;
    int k = 2;

    fa_matricea(n, m, k);
    print(n, m);

    return 0;
}