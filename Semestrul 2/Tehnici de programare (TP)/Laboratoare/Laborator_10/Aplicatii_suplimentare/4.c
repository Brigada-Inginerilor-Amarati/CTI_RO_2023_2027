/*
Se dă un vector cu n elemente numere naturale. 

Folosind metoda Divide et Impera să se verifice dacă 

are elementele ordonate crescător.
*/

#include <stdio.h>

int sunt_sortate(int v[], unsigned stg, unsigned dr){
    unsigned mijloc = (stg + dr) / 2;

    if(stg >= dr){
        return 1;
    }

    if(v[mijloc] > v[mijloc + 1]){
        return 0;
    }

    return sunt_sortate(v, stg, mijloc) && sunt_sortate(v, mijloc + 1, dr);

}

int main(void){
    int v[] = {1,2,3,4};
    int u[] = {2,1,3,2};

    printf("%d %d", sunt_sortate(v, 0, 3), sunt_sortate(u, 0, 3));
    return 0;
}