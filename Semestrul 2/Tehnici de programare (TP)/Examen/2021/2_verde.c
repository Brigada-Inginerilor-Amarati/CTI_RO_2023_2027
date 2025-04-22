#include <stdio.h>
#include <stdlib.h>

#define MAX_LEVEL 10

int st[MAX_LEVEL];

int eValid(int st[], int k, int n){
    int suma = 0;
    
    if(st[k] < st[k -1]){
        return 0;
    }

    for(int i=1; i<= k; i++){
        suma += st[i];
        if (suma > n){
            return 0;
        }
    }
    return 1;
}

int solutie(int st[], int k, int n){
    int suma = 0;
    for(int i = 1; i <= k; i++){
        suma += st[i];
    }
    return suma == n;
}

void afiseazaSol(int st[], int k, int n){
    for (int i=1; i<k; i++){
        printf("%d + ", st[i]);
    }
    printf("%d", st[k]);
    printf("\n");
}

void back_rec(int st[], int k, int n){
    if (k>=MAX_LEVEL){
        perror("depasirea stivei locale\n");
        return;
    }
    for (int i=1; i<=3; i++){   //acestia sunt succesorii posibili
        st[k]=i;                //pune acel succesor pe nivel 
        if (eValid(st, k, n)){
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


int main(int argc, char **argv){
    if(argc != 2){
        return -1;
    }

    int n = atoi(argv[1]);

    back_rec(st, 1, n);

    return 0;
}