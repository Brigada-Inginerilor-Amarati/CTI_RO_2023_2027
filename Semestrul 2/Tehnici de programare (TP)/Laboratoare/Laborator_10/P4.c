/*
4. Se citesc doua numere naturale, n si m, urmate de un sir de 

n numere naturale, ordonate crescator si urmate de m perechi de elemente naturale,

 x si y. Sa se determine cate dintre intervalele [x, y] contin cel putin un element din sir.
*/

#include <stdio.h>
#include <stdlib.h>

int cautaBin(int x, int y, int v[], unsigned stg, unsigned dr){
    if(dr < stg){
        return -1;
    }

    unsigned mijloc = (stg + dr) / 2;

    if(v[mijloc] < x){
        return cautaBin(x, y, v, mijloc + 1, dr);
    }

    if(v[mijloc] > y){
        return cautaBin(x, y, v, stg, mijloc - 1);
    }

    return mijloc;
}

int main(int argc, char ** argv){
    if(argc != 2){
        return -1;
    }
    int n = 6; // n nr naturale
    int m = atoi(argv[1]); // m perechi de numere naturale

    int v[] = {2, 7, 8, 11, 15, 17};

    int nr = 0;

    for(int i = 0; i < m; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        int index = cautaBin(x, y, v, 0, 5);
        if (index != -1)
        {
            nr++;
        }
    }

    printf("%d \n", nr);


    return 0;
}