/*
1. Se citesc dintr-un fisier transmis ca si parametru in linie de comanda, 

un numar natural n (n<=100000) si apoi n numere intregi. 

Se parcurge vectorul format din aceste numere, salvand sumele elementelor consecutive. 

Dupa fiecare parcurgere se afiseaza numarul iteratiei si vectorul rezultat. 

Se va repeta acest pas pana cand vectorul va contine un singur numar.

Exemplu

intrare:

5
2 5 7 -3 9

Afiseaza:
Iteratia 1: 7 12 4 6
Iteratia 2: 19 16 10
Iteratia 3: 35 26
Iteratia 4: 61
*/

#include <stdio.h>
#include <stdlib.h>

int iteratie = 1;

void adunare_recursiva(int *v, int n){
    if(n <= 1){
        return ;
    }

    for(int i = 0; i < n - 1; i++){
        v[i] = v[i] + v[i + 1];
    }
    
    n --;

    printf("Iteratia %d : ", iteratie);
    for(int i = 0; i < n; i++){
        printf("%d ", v[i]);
    }
    
    putchar('\n');
    iteratie++;

    return adunare_recursiva(v, n);
}

int main(int argc, char ** argv){
    if(argc != 2){
        printf("error using arguments \n");
        return -1;
    }

    FILE *fin = NULL;

    if((fin = fopen(argv[1], "r")) == NULL){
        printf("Eroare deschidere fisiere.\n");
        return -2;
    }

    int n = 0;
    fscanf(fin, "%d", &n);

    int *v = NULL;
    if((v = malloc(n * sizeof(int))) == NULL){
        printf("eroare alocare dinamica \n");
        return -1;
    }

    //citire vector
    for(int i = 0; fscanf(fin, "%d", &v[i]) != EOF; i++);

    fclose(fin);

    adunare_recursiva(v, n);

    free(v);
    
    return 0;
}