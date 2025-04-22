/*
2. Folosind metoda Divide et Impera, scrieți funcția recursivă cu antetul 

int NrXDivImp(int a[], int st, int dr, int x)

care primind ca parametri un vector a de numere întregi și trei numere întregi st, dr și x, 

returnează numărul de apariții ale numărului x în vectorul secvența a[st], a[st+1], ..., a[dr].
*/

#include <stdio.h>

int NrXDivImp(int a[], int st, int dr, int x){
    if(st > dr){
        return 0;
    }

    unsigned mijloc = (st + dr) / 2;

    if(st == dr){
        if (a[st] == x)
        {
            return 1;
        }
        else{
            return 0;
        }
        
    }

    return NrXDivImp(a, st, mijloc, x) + NrXDivImp(a, mijloc + 1, dr, x); 
}

int main(void){
    int v[] = {1, 2, 13, 2, 13, 4, 5, 13};

    int x = 13;

    int nr = NrXDivImp(v, 0, 7, x);

    printf("%d \n", nr);

    return 0;
}