/*
Sa se genereze toate permutarile multimii {1, 2, ...N}, in ordine lexicografica.

Date de intrare

In fisierul de intrare permutari.in se gaseste pe prima linie numarul natural N.
Date de iesire

In fisierul de iesire permutari.out se vor afisa permutarile multimii, fiecare pe cate o linie.
Restrictii

§  1 ≤ N ≤ 8
Exemplu

permutari.in
	

permutari.out

3
	

1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1

Problema se va rezolva utilizand un algoritm de backtracking.
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE_ST 100

int avemSuccesor(int stiva[], int k, int n) {
    if (stiva[k] < n) {
        stiva[k]++;
        return 1;
    }
    return 0;
}

int eValid(int stiva[], int k) {
    for (int i = 1; i < k; i++) {
        if (stiva[i] == stiva[k]) {
            return 0;
        }
    }
    return 1;
}

int eSolutie(int stiva[], int k, int n) {
    return k == n;
}

void tipar(int stiva[], int k, FILE *fout) {
    for (int i = 1; i <= k; i++) {
        fprintf(fout, "%d ", stiva[i]);
    }
    fprintf(fout, "\n");
}

void back(int n, FILE *fout) {
    int stiva[SIZE_ST] = {0};
    int k = 1;
    stiva[k] = 0;

    while (k > 0) {
        if (avemSuccesor(stiva, k, n)) {
            if (eValid(stiva, k)) {
                if (eSolutie(stiva, k, n)) {
                    tipar(stiva, k, fout);
                } else {
                    k++;
                    stiva[k] = 0;
                }
            }
        } else {
            k--;
        }
    }
}

int main(void) {
    FILE *fin = fopen("permutari.in", "r");
    FILE *fout = fopen("permutari.out", "w");

    if (fin == NULL) {
        printf("Eroare deschidere fișier date intrare\n");
        return -1;
    }

    if (fout == NULL) {
        printf("Eroare deschidere fișier date ieșire\n");
        fclose(fin);
        return -1;
    }

    int n;
    fscanf(fin, "%d", &n);

    back(n, fout);

    fclose(fin);
    fclose(fout);

    return 0;
}
