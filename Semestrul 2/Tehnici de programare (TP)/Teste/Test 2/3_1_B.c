/*
Se da un numar natural n,
    drept unic parametru in linie de comanda n apartine [1, 9].
Sa se genereze o matrice patratica de dimensiune 2^n - 1,
    dupa urmatoarele reguli:

        - elementul din mijlocul matricii este egal cu n
        - elementele de pe linia mediana si cele de pe coloana mediana (exceptand elementul din mijlocul matricii) sunt nule
        - folosind linia mediana si coloana mediana,
            se imparte matricea in alte 4 matrici care se genereaza similar,
            dar au dimensiunea 2^(n - 1) - 1
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_LENGTH 512

int f (int n) { return pow(2, n) - 1; }

void generateMatrix(unsigned a[][MAX_LENGTH], int i, int j, int n) {    //  i si j for fi indecsii de la inceputul liniei si coloanei respectiv
    if (!n) //  daca n = 0 oprim
        return ;
    
    int dimensiune = f(n);
    int mediana = dimensiune / 2;

    for (int l = 0; l < dimensiune; l ++) { //  setam pe 0 linia si coloana mediana
        a[i + mediana][j + l] = 0;
        a[i + l][j + mediana] = 0;
    }
    a[i + mediana][j + mediana] = n;    //  setam pe n elementul din mijlocul matricii / submatricii
    //  aici impartim din nou in cele 4 patrate delimitate de mediana pe linii si coloane
    generateMatrix(a, i, j, n - 1);
    generateMatrix(a, i, j + mediana + 1, n - 1);
    generateMatrix(a, i + mediana + 1, j, n - 1);
    generateMatrix(a, i + mediana + 1, j + mediana + 1, n - 1);
}

void printMatrix (unsigned a[][MAX_LENGTH], int n) {
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++)
            printf("%d ", a[i][j]);
        putchar('\n');
    }
}

int main (int argc, char** argv) {
    if (argc != 2) {
        printf("eroare argumente\n");
        return -1;
    }

    int n = atoi(argv[1]);
    int dimensiune = f(n);  //  dimansiunea -> 2^n - 1

    unsigned a[MAX_LENGTH][MAX_LENGTH];
    generateMatrix(a, 0, 0, n);
    printMatrix(a, dimensiune);

    return 0;
}