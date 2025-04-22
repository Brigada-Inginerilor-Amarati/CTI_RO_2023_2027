#include <stdio.h>
#include "back.h"

int avemSuccesor(int st[], int k, int n){
    if (st[k]<n){
        st[k]++;
        return 1;
    }
    return 0;
}

int eValid(int st[], int k){
    for (int i=1; i<k;i++){
        if (st[i]==st[k]){  //inseamna ca se mai repeta undeva acelasi element
            return 0;
        }
    }
    return 1;
}

int eValidComb(int st[], int k){
    for (int i=1; i<k; i++){
        if (st[i]>=st[k]){
            return 0;
        }
    }
    return 1;
}

int eSolutiePerm (int st[], int k, int payload[]){

    return k==payload[0];   //prin conevnetie payload[0] pastreaza n-ul problemei
}

int eSolutieAranj (int st[], int k, int payload[]){
    return k==payload[1];//prin conevnetie payload[1] pastreaza p-ul problemei
}

void afiseazaSolutie(int st[], int k){
    for (int i=1; i<=k; i++){
        printf("%d ", st[i]);
    }
    printf("\n");
}


int main(){

    
    
    
    
    printf("Permutari:\n");
    int payloadPerm[MAX_PAYLOAD]={3,3};
    BackBehaviour_t behPerm={payloadPerm, avemSuccesor, eValid, eSolutiePerm, afiseazaSolutie};
    back(behPerm);
    printf("Aranjamanet:\n");
    int payloadAranj[MAX_PAYLOAD]={5,3};
    BackBehaviour_t behAranj={payloadAranj, avemSuccesor, eValid, eSolutieAranj, afiseazaSolutie};
    back(behAranj);
    printf("Combinari:\n");
    int payloadComb[MAX_PAYLOAD]={5,3};
    BackBehaviour_t behComb={payloadComb, avemSuccesor, eValidComb, eSolutieAranj, afiseazaSolutie};
    back(behComb);
    return 0;
}