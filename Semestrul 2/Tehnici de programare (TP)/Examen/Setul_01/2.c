/*
2. Se citesc dintr-un fisier transmis ca si parametru in linie de comanda 

doua numere naturale n si s (n<=10, s<=20). 

Afisati in ordine crescatoare toate numerele cu n cifre 

care au suma cifrelor egala cu s 

si in care oricare doua cifre alaturate au paritate diferita.


Exemple: n=4, s=8 => 1016, 1034, 1052, 1070, 1214, 1232, ... 7010
*/
#include <stdio.h>
#include <stdlib.h>

int avemSuccesor(int stiva[], int k, int n){
    if(stiva[k] < 9){
        stiva[k]++;
        return 1;
    }

    return 0;
}

int eValid(int stiva[], int k, int n){
    if(k > n){
        return 0;
    }
    for(int i = 2; i <=k; i++){
        if(stiva[i - 1] %2 == stiva[i] % 2){ // 2 cifre consecutive cu aceeasi paritate
            return 0;
        }
    }
    if(stiva[1] == 0) return 0;
    return 1;
}


int eSolutie(int stiva[],int k, int n, int s){
    int suma = 0;
    for(int i = 1; i <= k; i++){
        suma += stiva[i];
    }

    if(suma != s){
        return 0;
    }

    return k == n; 
}

void afisare(int stiva[], int k){
    for(int i = 1; i <= k; i++){
        printf("%d ", stiva[i]);
    }

    printf("\n");
}

int back(int n, int s){
    int stiva[11] = {0};
    int k = 1;
    int perm = 0;
    stiva[k] = -1;

    while (k > 0)
    {
        if(avemSuccesor(stiva, k, n)){
            if(eValid(stiva, k, n)){
                if(eSolutie(stiva, k, n, s)){
                    afisare(stiva, k);
                    perm++;
                }
                else{
                    k++;
                    stiva[k] = -1;
                }
            }
            else{
                ;
            }
        }
        else{
            k--;
        }
    }
    return perm;
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
    int s = 0;

    fscanf(fin, "%d %d", &n, &s);


    back(n, s);

    fclose(fin);
    return 0;
}