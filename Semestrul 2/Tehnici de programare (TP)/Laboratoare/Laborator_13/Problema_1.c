/*
1. Scrieți un program care citește un număr natural n cu cifre distincte 

și care să calculeze și să afișeze suma S a tuturor numerelor obținute 

prin rearanjarea cifrelor lui n.
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_LEVEL 10

// int succesor(int st[], int k, int n){
//     if (st[k]<n){
//         st[k]++;
//         return 1;
//     }
//     else{
//         return 0;
//     }
// }


int nr_cifre(int x){
    int nr_cifre = 0;
    while(x){
        nr_cifre++;
        x = x / 10;
    }

    return nr_cifre;
}

int eValid(int st[], int k){
    for(int i=1; i<k; i++){
        if (st[k]==st[i]){
            return 0;
        }
    }
    return 1;
}

int solutie(int st[], int k, int nr_cif){
    return k == nr_cif;
}

void afiseazaSol(int st[], int k, int n){
    for (int i=1; i<=k; i++){
        printf("%d ", st[i]);
    }
    printf("\n");
}

int concateneaza(int st[], int nr_cifre){
    int nr = 0;
    for (int i = 1; i <= nr_cifre; i++){
        nr = nr * 10 + st[i];
    }
    return nr;
}

int suma = 0;

void back_rec(int st[], int k,int nr_cif){
    if (k>=MAX_LEVEL){
        perror("depasirea stivei locale\n");
        return;
    }
    
    for (int i=1; i<=nr_cif; i++){   //acestia sunt succesorii posibili
        st[k]=i;                //pune acel succesor pe nivel 
        if (eValid(st, k)){
            if (solutie(st, k, nr_cif)){
                afiseazaSol(st, k, nr_cif);
                suma = suma + concateneaza(st, nr_cif);
            }
            else{
                back_rec(st, k+1, nr_cif);   //rec ~ k=k+1
                /*daca avem o configuratie partiala, valida, dar care
                nu e solutie (~inca nu e destul) --> trebuie sa trecem
                la nivelul urmator
                */
            }
        }
        else{
            ;   //daca nu e valid doar se va trece la urmatorul
        }
    }
    /* la incehiere for-ului se incheie apelul curent de functie
    --> se continua de pe "nivelul" anterior (din stack)
    */
}

int main(int argc, char* argv[]){
    
    if (argc<2) return -1;
    int n=atoi(argv[1]);
    
    int nr_cif = nr_cifre(n);

    int st[MAX_LEVEL]={0};

    back_rec(st, 1, nr_cif);
    printf("%d \n", suma);
    return 0;
}