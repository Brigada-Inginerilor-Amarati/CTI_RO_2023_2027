/*
Se considera un fiser text care pe prima linie are un numar natural n, 

pe a doua linie o lista de n numere intregi,

ordinate crescator, iar pe urmatoarele linii (pana la sfarsitul fisierului) 

perechi de numere intregi a, b. Se cere determinarea

intervalelor [a, b] care includ cel putin un element din lista de valori aflata

pe randul al doilea al fisirului

Implementati un program C care primeste ca si parametru o cale de fisier text

cu formatul descris mai sus si afiseaza pe

iesirea standard lista intervalelor care satisfac conditia prezentata, incheiata 

cu numaru de asemena intervale.
*/

#include <stdio.h>
#include <stdlib.h>

int cautare_binara(int *v, int x, int y, int valoare_cautata){
    if(x > y){
        return 0;
    }

    int mijloc = (x + y) / 2;

    if(v[mijloc] == valoare_cautata){
        return 1;
    }

    if(v[mijloc] > valoare_cautata){
        return cautare_binara(v, x, mijloc - 1, valoare_cautata);
    }

    return cautare_binara(v, mijloc + 1, y, valoare_cautata);
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

    int a = 0;
    int b = 0;

    int count = 0;

    while (fscanf(fin, "%d %d", &a, &b) != EOF){
        if(a > b){
            int temp = a;
            a = b;
            b = temp;
        }

        for(int i = a; i <= b; i++){
            if(cautare_binara(v, 0, n - 1, i)){
                count++;
                printf("[%d ; %d] \n", a, b);
                break;
            }
        }
    }

    printf(" Nr de intervale este : %d \n", count);
    
    free(v);

    return 0;
}