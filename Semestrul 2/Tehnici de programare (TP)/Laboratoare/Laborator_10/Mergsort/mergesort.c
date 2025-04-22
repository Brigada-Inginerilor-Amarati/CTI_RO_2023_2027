#include <stdio.h>
#include <string.h>
#include "rand_array.h"

void printTab(int t[], int n){
    for (int i=0; i<n; i++){
        printf("%d ", t[i]);
    }
    printf("\n");
}

void mergeSort(int v[], int stg, int dr){
    printf("Stg= %d Dr= %d ", stg, dr);

    if (stg==dr){
        ;
    }
    else{

        int mij=(stg+dr)/2;

        mergeSort(v, stg, mij);
        mergeSort(v, mij+1, dr);

        int aux[dr-stg+100];
        memset(aux, 0, dr-stg+100);

        int k=0;
        int i=stg;
        int j=mij+1;

        while (i<=mij && j<=dr){    //cat timp nu am ajuns la capatul niciunuia dintre vectori
            if (v[i]<v[j]){         //verificam care este elemuntul mai mic si il copiem in aux
                aux[k]=v[i];
                i++;
                k++;
            }
            else{
                aux[k]=v[j];
                j++;
                k++;
            }
        }
        
        while (i<=mij){             //copiem elementele de la capatulul unuia dintre vecotri
            aux[k]=v[i];
            k++;
            i++;
        }
        while (j<=dr){              //sau de la capatulc celuilalt
            aux[k]=v[j];
            k++;
            j++;
        }

        for (int i=0; i<k; i++){
            v[stg+i]=aux[i];
        }
        printTab(v, 9);
    }
}

int main(void){
    int v[] = {3,41,132,13,3,1,0};

    mergeSort(v, 0, 6);

    print_int_array(v, 7);

    return 0;
}