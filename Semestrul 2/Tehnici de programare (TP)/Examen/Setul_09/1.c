/*
Sa se scrie un program care primeste ca argument din linia de 

comanda un numar natural n<3000. Programul va descompune acest numar 

n ca suma de puteri crescatoare ale lui 2. Functia pentru descompunerea 

lui n va fi implementata recursiv.

Exemplu: Pentru n=86 va afisa 2 4 16 64 (86 se descompune ca 2+4+16+64)

Hint: exista un  k=log2(N), putere maxima a lui 2 pentru care 2^k<=n
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void descompunere(int n){
    if(n == 0){
        return ;
    }

    int putere_max = (int) log2f(n);
    //calculam care este maximul lui 2 ^ puteremax care incape in n
    int putere = 1 << putere_max;

    descompunere(n - putere);

    printf("%d ", putere);
}

int main(int argc, char**argv){
    if(argc != 2){
        printf("incorect ussage of arguments \n");
        return -1;
    }

    int n = atoi(argv[1]);

    if(n <= 0 || n >= 3000){
        printf("N ai dat bine n");
        return 1;
    }

    descompunere(n);
    printf("\n");

    return 0;
}