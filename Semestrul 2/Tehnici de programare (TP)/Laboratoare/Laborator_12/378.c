/*
[PBINFO378] Un student are de dat n examene numerotate de la 1 la n 

intr-o sesiune formata din m zile (m este cel putin de 2 ori mai mare decat n).

Afisati toate modurile in care isi poate programa studentul examenele 

astfel incat sa nu dea 2 examene in zile consecutive si sa dea examenele 

in ordine de la 1 la n.

Ex:
n=3
m=6
Solutii:
010203
100203
102003
102030
(0 codifica zilele libere)
*/

#include <stdio.h>
#include <stdlib.h>

int avemSuccesor(int stiva[], int k, int n){
    if(stiva[k] < n){
        stiva[k]++;
        return 1;
    }

    return 0;
}

int eValid(int stiva[], int k, int n, int m){
    
    int examen = -1;
    int cnt = 0;

    for(int i = 1; i <= k; i++){
        if(stiva[i] != 0 && examen == -1){
            examen = stiva[i];
        } // vrem sa vedem daca examenele sunt puse in ordine
        else if(stiva[i] != 0 && examen != -1){ //aici avem deja un prim examen setat
            if(stiva[i] <= examen){ //cautam urmatorul examen adica 2 > 1 3 > 1, nu 1 > 2
                return 0;
            }
            examen = stiva[i];
        }

    }

    for(int i = 2; i <=k; i++){
        if(stiva[i - 1] != 0 && stiva[i] != 0){ //ambele examene sunt in zile consecutive
            return 0;
        }
    }

    if(k == m){
        for(int i = 1; i <= k; i++){
            if(stiva[i] != 0){
                cnt++;
            }
        }
        if(cnt != n){
            return 0;
        }
    }

    return 1;
}


int eSolutie(int stiva[],int k, int m){
    return k == m; //nr de zile
}

void afisare(int stiva[], int k){
    for(int i = 1; i <= k; i++){
        printf("%d ", stiva[i]);
    }

    printf("\n");
}

int back(int n, int m){
    int stiva[10] = {0};
    int k = 1;
    int perm = 0;
    stiva[k] = -1;

    while (k > 0)
    {
        if(avemSuccesor(stiva, k, n)){
            if(eValid(stiva, k, n, m)){
                if(eSolutie(stiva, k, m)){
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

int main(void){

    int n = 4, m = 8;
    back(n, m);
    return 0;
}