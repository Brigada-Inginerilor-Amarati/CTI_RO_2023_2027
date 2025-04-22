/*
[MCIP631] Se citeste un numar natural n. Generati si afisati

toate combinatiile de cate n cifre binare care nu au doua cifre de 1 alaturate.

Exemplu:
n=3
combinatiile sunt:
0 0 0
0 0 1
0 1 0
1 0 0
1 0 1
*/

// pune -1 in biblioteca la st[k] = 0; ---> st[k] = -1;
#include <stdio.h>
#include <stdlib.h>
#include "back.h"

int avemSuccesor(int stiva[], int k, int n){
    //verificam ce nr avem voie sa generam -> {0, 1}
    if(stiva[k] < 1){
        stiva[k]++;
        return 1;
    }

    return 0;
}

int eValid(int stiva[], int k){
    for(int i = 2; i <=k; i++){
        if(stiva[i - 1] == 1 && stiva[i] == 1){
            return 0;
        }
    }

    return 1;
}

int eSolutie(int stiva[], int k, int payload[]){
    return k == payload[0];
}

void afiseazaSolutie(int stiva[], int k){
    for(int i = 1; i <= k; i++){
        printf("%d ", stiva[i]);
    }

    printf("\n");
}

int main(void){

    int n = 3;

    int payload[] = {n, n};
    BackBehaviour_t nr = {payload, avemSuccesor, eValid, eSolutie, afiseazaSolutie};

    back(nr);
    return 0;
}