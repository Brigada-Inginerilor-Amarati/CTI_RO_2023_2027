/*
 Se dă numărul natural n.
 
Determinati o modalitate de așezare a numerelor
 
din mulțimea 1,2,…,n pe un cerc astfel încât 

suma a oricare două nume învecinate să fie 

pătrat perfect.
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int ePatratPerfect(int nr){
    int radacina = sqrt(nr);

    return radacina * radacina == nr;
}

int avemSuccesor(int stiva[], int k, int n){
    if(stiva[k] < n){
        stiva[k]++;
        return 1;
    }

    return 0;
}

int eValid(int stiva[], int k){
    for(int i = 1; i < k; i++){
        if(stiva[i] == stiva[k]){
            return 0;
        }
    }

    //stiva[i] + stiva[i - 1] -> patrat perfect

    // for(int i = 2; i <= k; i++){
    //     if(!ePatratPerfect(stiva[i] + stiva[i - 1])){
    //         return 0;
    //     }
    // }

    if(k > 1){
        return ePatratPerfect(stiva[k] + stiva[k - 1])  ;
    }
    
    return 1;
}

int eSolutie(int stiva[], int k, int n){
    if(k != n){
        return 0;
    }

    return ePatratPerfect(stiva[1] + stiva[n]);
}

void afiseazaSolutie(int stiva[], int n){
    for(int i = 1; i <= n; i ++){
        printf("%d ", stiva[i]);
    }

    printf("\n");
}

void back(int n){
    int stiva[100] = {0};
    int k = 1;

    // stiva[k] = 0;

    while(k > 0){
        if(avemSuccesor(stiva, k, n)){
            if(eValid(stiva, k)){
                if(eSolutie(stiva, k, n)){
                    afiseazaSolutie(stiva, n);
                }
                else{
                    k++;
                    stiva[k] = 0;
                }
            }
            else{
                ;
            }
        }
        else{
            k --;
        }
    }
}

int main(int argc, char** argv){
    back(atoi(argv[1]));
    
    return 0;
}