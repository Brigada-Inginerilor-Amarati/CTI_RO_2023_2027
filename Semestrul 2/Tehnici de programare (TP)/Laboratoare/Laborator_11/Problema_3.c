/*
3. Cunoscând timpul necesar pentru analizarea fiecărui proiect, 

scrieţi un program care determină ordinea în care vor fi analizate 

proiectele, astfel încât timpul mediu de aşteptare pentru investitori 

să fie minim. Drept date de intrare se cunosc n (numarul de proiecte) 

si o lista de valori numerice naturale reprezentand timpii de evaluare 

pentru fiecare proiect (in unitati abstracte de timp)

*/

#include <stdio.h>
#include <stdlib.h>

int comparare_timp(const void *a, const void *b){
    const int* p1 = (const int*)a;
    const int* p2 = (const int*)b;

    if(*p1 < *p2){
        return -1;
    }

    if(*p1 > *p2){
        return 1;
    }

    return 0;
}

int main(void){
    int n = 5;
    int v[] = {9, 11, 30, 7, 1};

    qsort(v, n, sizeof(int), comparare_timp);

    for(int i = 0; i < n; i++){
        printf("%d ", v[i]);
    }

    printf("\n");

    

    return 0;
}