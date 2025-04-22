/*
[MCIP811] Se citesc numerele naturale n,a,b,p,q (n<=20, a<=b<=n, p<=q) 

si apoi n punctaje diferite ale unor intrebari.


Sa se afiseze toate modurile in care se poate alege pentru un test 

un numar de intrebari cuprins intre a si b 

si care sa aiba punctajul total intre p si q.

Exemplu:
7 4 5 20 25  n , a, b, p, q -> n punctaje, a < nr intrebari < b < n; p < punctaj < q

6
5
7
8
2
3
10

se vor afisa
6 5 7 2
6 5 7 2 3
6 5 7 3
6 5 8 2
6 5 8 2 3
....
8 2 3 10
*/

#include <stdio.h>
#include <stdlib.h>

int v[] = {6, 5, 7, 8, 2, 3, 10}; // punctajele
int n = 7; // nr punctaje
int a = 4;
int b = 5;
int p = 20;
int q = 25;
 
int avemSuccesor(int stiva[], int k, int n){
    //asta ne genereaza indecsi de la 1 pana la n
    if(stiva[k] < n){
        stiva[k]++;
        return 1;
    }

    return 0;
}

int eValid(int stiva[], int k, int n){
    int suma = 0;
    for(int i = 1; i < k; i++){
        if(stiva[i] == stiva[k]){ //asta ca sa nu avem indecsi egali, adica sa nu avem aceeasi intrebare de 2 ori
            return 0;
        }
    }

    return 1;
}


int eSolutie(int stiva[],int k, int a, int b){
    if(k < a || k > b){
        return 0;
    }
    int suma = 0;
    for(int i = 1; i <= k; i++){
        suma += v[stiva[i] - 1];
    }
    return (suma >= p && suma <= q);
}

void afisare(int stiva[], int k){
    for(int i = 1; i <= k; i++){
        printf("%d ", v[stiva[i] - 1]);
    }

    printf("\n");
}

int back(){
    int stiva[20] = {0};
    int k = 1;
    int perm = 0;
    stiva[k] = 0;

    while (k > 0)
    {
        if(avemSuccesor(stiva, k, n)){
            if(eValid(stiva, k, n)){
                if(eSolutie(stiva, k, a, b)){
                    afisare(stiva, k);
                    perm++;
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
            k--;
        }
    }
    return perm;
}

int main(void){

    back();
    return 0;
}