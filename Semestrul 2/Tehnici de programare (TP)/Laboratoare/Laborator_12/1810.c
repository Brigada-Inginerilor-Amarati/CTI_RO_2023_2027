/*
[PBINFO1810] Scrieți un program care citeşte o 

valoare naturală nenulă impară pentru n şi apoi generează 

şi afişează în ordine crescătoare lexicografic toate combinaţiile 

formate din n cifre care îndeplinesc următoarele proprietăţi:

- încep şi se termină cu 0;

- modulul diferenţei între oricare două cifre alăturate dintr-o combinaţie este 1.

Astfel, pentru n=5, combinaţiile afişate sunt, în ordine, următoarele: 01010, 01210.
*/

#include <stdio.h>
#include <stdlib.h>

int avemSuccesor(int stiva[], int k, int n){
    if(stiva[k] < n / 2){
        stiva[k]++;
        return 1;
    }

    return 0;
}

int eValid(int stiva[], int k, int n){
    if(k == n){
        if(stiva[n] != 0){
            return 0;
        }
    }

    if(stiva[1] != 0){
        return 0;
    }

    for(int i = 2; i <= k; i++){
        if(abs(stiva[i] - stiva[i - 1]) != 1){
            return 0;
        }
    }

    return 1;
}


int eSolutie(int stiva[],int k, int n){
    return k == n;
}

void afisare(int stiva[], int k){
    for(int i = 1; i <= k; i++){
        printf("%d ", stiva[i]);
    }

    printf("\n");
}

int back(int n){
    int stiva[10] = {0};
    int k = 1;
    int perm = 0;
    stiva[k] = -1;

    while (k > 0)
    {
        if(avemSuccesor(stiva, k, n)){
            if(eValid(stiva, k, n)){
                if(eSolutie(stiva, k, n)){
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

    int n = 5;

    back(n);
    return 0;
}