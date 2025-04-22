/*
matrice de n linii, n coloane si elemente < 1000

sa se afiseze in ordine crescatoare valorile care apar sub

d.p si d.s de cel putin 2 ori. fiecare valoare se va afisa o singura data.
*/

#include <stdio.h>
#include <stdlib.h>


#define MAX 10

void frecv(int matrice[][MAX], int frecventa[1000], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i > j && (i + j > n - 1)){
                frecventa[matrice[i][j]] = frecventa[matrice[i][j]] + 1;
            }
        }
    }
}

int main(void){

    int *frecventa = calloc(1000 , sizeof(int));
    int matrice[MAX][MAX];
    int n = 6;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &matrice[i][j]);
        }
    }

    frecv(matrice, frecventa, n);

    for(int i = 0; i < 1000; i++){
        if(frecventa[i] >= 2){
            printf("%d ", i);
        }
    }
    printf("\n");

    free(frecventa);
    return 0;
}