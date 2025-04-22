/*
Se considera un fisier care contine pe prima un numar n, 

iar pe a doua linie un sir de n numere naturale din

intervalul [0, 100], separate prin cate un spatiu. 

Se cere sa se determine toate perechile distincte formate din termeni ai sirului

aflat ın fisier, x si y (y − x ≥ 2), astfel ıncat sa nu existe niciun termen al sirului

care sa apartina intervalului (x,y). Numerele

din fiecare pereche sunt afisate pe cate o linie a ecranului, ın ordine strict crescatoare, 

separate printr-un spatiu, iar daca nu

exista nicio astfel de pereche, se afiseaza pe ecran mesajul nu exista. 

Implementati un program C care primeste calea catre

fisier ca si parametru in linie de comanda si afiseaza rezultatul la iesirea standard. 

Se va oferi un algoritm cu complexitate in timp maxim liniara.
*/

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
    int p1 = *(int *) a;
    int p2 = *(int *) b;

    if(p1 < p2){
        return -1;
    }

    if(p1 > p2){
        return 1;
    }

    return 0;
}

int main(int argc, char **argv){
    if(argc != 2){
        return -1;
    }

    FILE *fin = fopen(argv[1], "r");

    if(fin == NULL){
        printf("Nu s-a putut deschide fisierul \n");
        return -2;
    }

    int n = 0;

    fscanf(fin, "%d", &n);

    int *v = malloc(n * sizeof(int));

    if(v == NULL){
        printf("eroare la alocarea memoriei\n");
        return -3;
    }

    for(int i = 0; i < n; i++){
        fscanf(fin, "%d", &v[i]);
    }

    fclose(fin);

    qsort(v, n, sizeof(int), cmp);

    int valid = 0;

    for(int i = 0; i < n - 1; i++){
        //verificam sa respecte prima conditie
        if(v[i + 1] - v[i] >= 2){
            printf("(%d, %d) \n", v[i], v[i+1]);
            valid = 1;
        }
    }

    if(valid == 0){
        printf("nu exista");
    }

    return 0;
}