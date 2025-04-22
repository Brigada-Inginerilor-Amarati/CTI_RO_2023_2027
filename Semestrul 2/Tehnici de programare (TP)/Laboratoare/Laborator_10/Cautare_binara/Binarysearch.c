/*
a) Implementati o functie recursiva cu antetul int cautaBin(int x, int v[], unsigned stg, unsigned dr);

care cauta elementul x in tabloul v ordonat (nu conteaza daca crescator sau descrescator) si 

returneaza pozitia pe care sa gaseste una dintre aparitiile lui x sau -1 daca x nu apare in tablou.

Indicatie: algoritmul a fost prezentat in pseudocod in cadrul sesiunii de curs din saptamana 7;


b) Implementati functia de mai sus, in maniera nerecursiva (iterativa)

Indicatie: puteti folosi descrierea in pseudocod de aici https://www.pbinfo.ro/articole/3633/cautarea-binara

c) masurati timpul de executie (sau alternativ numarul de apeluri ale functiei recursive) 

pe masura ce dimensiunea tabloului creste; estimati complexitatea
*/

#include <stdio.h>
#include <stdlib.h>
#include "/home/daria/Tehnici_de_programare/Proiect/rand_array.h"
#include <time.h>

int cautaBin(int x, int v[], unsigned stg, unsigned dr){
    if(dr < stg){
        return -1;
    }

    unsigned mijloc = (stg + dr) / 2;

    if(v[mijloc] == x){
        return mijloc;
    }

    if(v[mijloc] < x){
        return cautaBin(x, v, mijloc + 1, dr);
    }

    return cautaBin(x, v, stg, mijloc - 1);
}

int cautaBin_iterativ(int x, int v[], unsigned stg, unsigned dr){
    int poz = - 1;

    while(stg <= dr && poz == -1){
        unsigned mijloc = (stg + dr) / 2;

        if(v[mijloc] == x){
            poz = mijloc;
        }
        else if(v[mijloc] < x){
            stg = mijloc + 1;
        }
        else{
            dr = mijloc - 1;
        }
    }

    return poz;
}

int main(void){
    srand(time(NULL));

    int *v = makeRandFlexiArray(10, getIncreasing);

    int element = 10;

    int index_rec = cautaBin(element, v, 0, 10);
    int index_ite = cautaBin_iterativ(element, v, 0, 10);

    print_int_array(v, 10);

    printf("%d %d\n", index_ite, index_rec);


    return 0;
}