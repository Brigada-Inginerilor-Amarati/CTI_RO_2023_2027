/*
2. Se dă o mulțime cu n elemente, numere naturale. 

Afișați în ordine lexicografică toate permutările mulțimii date

în care elementele prime sunt puncte fixe (nu își schimbă poziția).
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_LEVEL 10

int v[10];

int este_prim(int nr){
    if(nr < 2){
        return 0;
    }

    for(int i = 2; i * i <= nr; i++){
        if(nr % i == 0){
            return 0;
        }
    }
    return 1;
}

int eValid(int st[], int k) {
    for (int i = 1; i < k; i++) {
        if (st[k] == st[i]) { // Verificăm dacă elementele sunt unice
            return 0; 
        }
    }

    for (int i = 1; i <= k; i++) {
        if (este_prim(v[st[i] - 1])) {
            if (st[i] != i) {
                return 0;
            }
        }
    }

    int nu_este_prim = -1;

    for(int i = 1; i <=k; i++){
        if(!este_prim(v[st[i] - 1])){
            if(nu_este_prim == - 1) {//nu am avut niciun nr neprim inainte
                nu_este_prim = st[i] - 1; //poz curenta din vectorul initial
            }
            else if(v[st[i] - 1] < v[nu_este_prim]){
                return 0;
            }
            else{
                nu_este_prim = st[i] - 1;
            }
        
        }
    }
    return 1;
}

int solutie(int st[], int k, int n){
    return k == n;
}

void afiseazaSol(int st[], int k, int n){
    for (int i=1; i<=k; i++){
        printf("%d ", v[st[i] - 1]);
    }
    printf("\n");
}


void back_rec(int st[], int k, int n){
    if (k>=MAX_LEVEL){
        perror("depasirea stivei locale\n");
        return;
    }
    
    for (int i=1; i<=n; i++){   //acestia sunt succesorii posibili
        st[k]=i;                //pune acel succesor pe nivel 
        if (eValid(st, k)){
            // for(int j = 1; j <=k; j++){
            //     printf("%d ", v[st[j] - 1]);
            // }
            //printf("\n");
            if (solutie(st, k, n)){
                afiseazaSol(st, k, n);
            }
            else{
                back_rec(st, k+1, n);   //rec ~ k=k+1
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
    
    for(int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }

    int st[MAX_LEVEL]={0};

    back_rec(st, 1, n);
    return 0;
}