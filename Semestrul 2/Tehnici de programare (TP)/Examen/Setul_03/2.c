/*
2. Se consideră n tipuri de bancnote, cu valorile v[1] v[2] ... v[n], 

ordonate strict crescător. Pentru fiecare tip de bancnote se știe numărul 

de bancnote disponibile c[1] c[2] ... c[n]. Se cere să se determine o modalitate 

de a plăti integral o sumă dată S cu bancnotele disponibile. 

Calea catre fisier va fi transmisa ca si parametru in linie de comanda.

Restricții și precizări

    1 ≤ n ≤ 6
    1 ≤ S ≤ 1000
    1 ≤ v[i] ≤ 100
    1 ≤ c[i] ≤ 10
    oricare variantă corectă de plată a sumei S va fi luată în considerare
    pentru toate seturile de date există soluție

Exemplu: fisier intrare urmat de rezultat afisat pe ecran
*/

#include <stdio.h>

#define MAX 20


int main(int argc, char **argv){
    if(argc != 2){
        printf("Incorect ussage of arguments\n");
        return -1;
    }

    FILE *fin = fopen(argv[1], "r");
    if(fin == NULL){
        printf("Nu s-a putut deschide fisierul de citire \n");
        return -2;
    }

    int n, Suma;

    fscanf(fin, "%d %d", &n, &Suma);

    int v[MAX], c[MAX];

    for(int i = 0; i < n; i++){
        fscanf(fin, "%d", &v[i]);
    }

    for(int i = 0; i < n; i++){
        fscanf(fin, "%d", &c[i]);
    }

    int suma_noua = 0;

    int bancnote_folosite[MAX] = {0};

    int nr = n;

    while (suma_noua < Suma)
    {
        if(n == 0) break;
       if(v[n -1] <= Suma - suma_noua && c[n - 1] > 0){
        suma_noua += v[n - 1];
        c[n - 1] --;
        bancnote_folosite[n - 1] ++;
       }
       else{
        n--;
       }
    }

    if (suma_noua < Suma)
    {
        printf("Nu ne-au ajuns banii \n");
        return -4;
    }
    
    FILE *fout = fopen("2_out.txt", "w");
    if(fout == NULL){
        printf("nu s-a putut deschide fisierul de scriere \n");
        return -3;
    }
    for(int i = 0; i < nr; i++){
        fprintf(fout, "%d ", bancnote_folosite[i]);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}