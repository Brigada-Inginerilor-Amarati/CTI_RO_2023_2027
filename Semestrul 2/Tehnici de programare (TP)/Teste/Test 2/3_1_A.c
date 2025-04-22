/*
Dintr un fisier,
    avand calea transmisa ca unic parametru in lnie de comanda,
    se citeste un numar natural n,
    iar apoi n numere intregi urmate de o colectie de perechi de numere intregi.
Sa se afiseze,
    cate unul pe linie,
    intervalele deschise care contin exact 1 element dintre cele n citite.
*/
#include <stdio.h>
#include <stdlib.h>

int cmp (const void* elem1, const void* elem2) {
    const int* el1 = (const int*)elem1;
    const int* el2 = (const int*)elem2;
    if (*el1 < *el2)
        return -1;
    if (*el1 > *el2)
        return 1;
    return 0;
}

int* readArray (FILE* fis, unsigned* n) {
    fscanf(fis, "%u", n);

    int* v;
    if ((v = malloc(*n * sizeof(int))) == NULL) {
        printf("memorie insuficienta\n");
        return NULL;
    }

    for (unsigned i = 0; i < *n; i ++)
        fscanf(fis, "%d", &v[i]);

    return v;
}

unsigned short search (int* v, int elem, unsigned stg, unsigned dr) {
    if (stg > dr)
        return 0;

    int mijl = (stg + dr) / 2;
    if (v[mijl] == elem)
        return 1;
    if (v[mijl] > elem)
        return search(v, elem, stg, mijl - 1);
    return search(v, elem, mijl + 1, dr);
}

int main (int argc, char** argv) {
    if (argc != 2) {
        printf("eroare argumente\n");
        return -1;
    }

    FILE* fis;
    if ((fis = fopen(argv[1], "r")) == NULL) {
        printf("eroare deschidere fisier\n");
        return -2;
    }

    unsigned n;
    int* v = readArray(fis, &n);
    if (!v) {
        fclose(fis);
        return -3;
    }

    qsort(v, n, sizeof(int), cmp);  //  sortez vectorul pt a l pregati pt cautarea binara

    int x, y, aux;
    unsigned gasit = 0;
    while (fscanf(fis, "%d %d", &x, &y) != EOF) {   //  citesc intervale pana la terminarea fisierului
        if (x > y) {                                //  daca x > y atunci interschimb valorile (asa vrea, nu zice, dar in exemplul dat asa face)
            aux = x;
            x = y;
            y = aux;
        }

        for (int i = x + 1; i < y; i ++)        //  aici in i stochez fiecare element care apartine (x, y) (interval DESCHIS ca asa cere in enunt)
            gasit += search(v, i, 0, n - 1);    //  cresc contorul de fiecare data cand gasesc pe i in v
        if (gasit == 1)                         //  daca contorul este 1 atunci afisez intervalul, altfel o iau de la inceput cu un alt interval citit
            printf("%d %d\n", x, y);
        gasit = 0;
    }

    free(v);
    fclose(fis);
    return 0;
}