/*
Se dau N dame şi o tablă de şah de dimensiune NxN. Să se găsească 

toate modalităţile de a aranja toate damele astfel încât oricare 

două dame să nu se atace. Două dame se atacă dacă se află pe aceeaşi linie, 

coloană sau diagonală. Se cere să se afişeze prima soluţie în ordine 

lexicografică şi numărul total de soluţii.

 
Date de intrare

Fişierul de intrare damesah.in va contine pe prima linie numărul natural N, 
având semnificaţia din enunţ.

 
Date de ieşire

În fişierul de ieşire damesah.out se vor găsi două linii. Pe prima linie va 

fi afişată prima soluţie în ordine lexicografică. Aceasta solutie va fi formată 

din N numere, al i-lea număr reprezentând coloana pe care se află dama de pe linia i. 

Pe cea de-a doua linie, se va găsi numărul total de soluţii.

Restricţii

§  4 ≤ N ≤ 13
Exemplu

damesah.in
4

damesah.out
2 4 1 3
2
Explicatie

Pentru N = 4 dame, prima solutie generata va fi 2 4 1 3. Fiecare numar V[i] 

reprezinta coloana pe care se va afla dama de pe linia i. S-au gasit in total 2 solutii.


Problema se va rezolva utilizand un algoritm de backtracking.
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int avemSuccesor(int stiva[], int k, int n){
    if(stiva[k] < n){
        stiva[k] ++;
        return 1;
    }

    return 0;
}

int eValid(int stiva[], int k){
    for(int i = 1; i < k; i++){
        if(stiva[i] == stiva[k]){
            return 0; //aceeasi coloana
        }

        if(abs(i - k) == abs(stiva[i] - stiva[k])){
            return 0;
        }
    }

    return 1;
}

int eSolutie(int stiva[], int n, int k){
    return n == k;
}

void back(int n){
    int st[SIZE] = {0};
    int k = 1;
    st[k] = 0;

    int index = 0;

    FILE *fout = fopen("damesah.out", "w");
    if(fout == NULL){
        printf("eroare deschidere fisier output\n");
        exit(-1);
    }

    while(k > 0){
        if(avemSuccesor(st, k, n)){

            if(eValid(st, k)){

                if(eSolutie(st, k, n)){

                    if(index == 0){
                        for(int i = 1; i <= k; i++){
                            fprintf(fout, "%d ", st[i]);
                        }
                    }
                    index++;
                }
                else{
                    k++;
                    st[k] = 0;
                }
            }
        }

        else{
            k--;
                }
    }

    fprintf(fout,"\n%d \n", index);

    fclose(fout);
}

int main(int argc, char **argv){
    if(argc != 2){
        printf("Incorect ussage of argument \n");
    }

    FILE *fin = fopen(argv[1], "r");

    if(fin == NULL){
        printf("Eroare deschidere fisier de citire\n");
        return -1;
    }

    int n;
    fscanf(fin, "%d", &n);

    back(n);

    return 0;
}

