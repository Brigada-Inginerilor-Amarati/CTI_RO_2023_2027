/*
se da un sir x format din n numere naturale nenule

pentru fiecare element xi din ser sa se verifice daca exista un nr k

a.i elementul xi = suma primelor k elemente din sir

intrare nr n apoi n numere separate prin spatii

iesire: pe linie i se scrie valoare k daca eleementul

xi = suma primelor k elemente din sir

0 in caz contrar
*/

#include <stdio.h>
#include <stdlib.h>

void citeste_date(int v[], int n){
    for(int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }
}

void printeaza_date(int v[], int n){
    for(int i = 0; i < n; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

int b_search(int suma[], int stg, int dr, int cautat){
    if(stg > dr){
        return -1;
    }

    int mijloc = (stg + dr) / 2;

    if(suma[mijloc] == cautat){
        return mijloc;
    }

    if(suma[mijloc] < cautat){
        return b_search(suma, mijloc + 1, dr, cautat);
    }
    else{
        return b_search(suma, stg, mijloc - 1, cautat);
    }

}



int main(void){

    int n = 0;

    scanf("%d", &n);

    int v[20];
    citeste_date(v, n);
    
    int sum[20];
    sum[0] = v[0];
    for(int i = 1; i < n; i++){
        sum[i] = sum[i - 1] + v[i]; //sunt stocate suma primele k elemente pe pozitii
    }

    printeaza_date(v, n);
    printeaza_date(sum, n);

    for(int i = 0; i < n; i++){
        int x = b_search(sum, 0, n - 1, v[i]);

        printf("%d \n", x + 1);
    }



    return 0;
}