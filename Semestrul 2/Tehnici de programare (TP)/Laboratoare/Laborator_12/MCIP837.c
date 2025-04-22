/*
[MCIP837] Se citeste un cuvant format din maxim 10 litere mici distincte.

Afisati in ordine lexicografica toate anagramele cuvantului citit care au 
 
proprietatea ca nu contin doua vocale alaturate si nici doua consoane alaturate 

(practic vocalele si consoanele trebuie sa alterneze).

Daca acest lucru nu este posibil se va afisa mesajul IMPOSIBIL.

Exemplu:
Daca s="cosmina"
anagramele vor fi:
caminos
camison
camonis
...
sonimac
Daca s="cosmin" se va afisa IMPOSIBIL
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 10

char cuvant[MAX_LEN] = "";

int avemSuccesor(int stiva[], int k, int n){
    if(stiva[k] < n){
        stiva[k]++;
        return 1;
    }

    return 0;
}

int esteVocala(char c){
    const char *vocale = "aeiouAEIOU";
    return strchr(vocale, c) != NULL;
}

int esteConsoana(char c){
    return isalpha(c) && !esteVocala(c);
}

int eValid(int stiva[], int k){
    if(stiva[0] == stiva[k]){
        return 0;
    }
    
    for(int i = 1; i < k; i++){
        if (stiva[i] == stiva[k]){
            return 0;
        }
    }

    for(int i = 1; i < k; i++){
        if(esteVocala(cuvant[stiva[i] - 1]) && esteVocala(cuvant[stiva[i + 1] - 1])){
            return 0;
        }
    }

    for(int i = 1; i < k; i++){
        if(esteConsoana(cuvant[stiva[i] - 1]) && esteConsoana(cuvant[stiva[i + 1] - 1])){
            return 0;
        }
    }
    return 1;
}


int eSolutie(int stiva[],int k, int n){
    return k == n;
}

void afisare(int stiva[], int k){
    for(int i = 1; i <= k; i++){
        printf("%c", cuvant[stiva[i] - 1]);
    }

    printf("\n");
}

int back(int n){
    int stiva[MAX_LEN + 1] = {0};
    int k = 1;
    int perm = 0;
    stiva[k] = 0;

    while (k > 0)
    {
        if(avemSuccesor(stiva, k, n)){
            if(eValid(stiva, k)){
                if(eSolutie(stiva, k, n)){
                    afisare(stiva, k);
                    perm++;
                }
                else{
                    k++;
                    stiva[k] = 0;
                }
            }
            else{
                ;
            }
        }
        else{
            k--;
        }
    }
    return perm;
}

int comparator(const void *a, const void *b){
    return *(char*) a - *(char *) b;
}


int main(int argc, char**argv){

    if(argc != 2){
        return -1;
    }

    strcpy(cuvant, argv[1]);

    qsort(cuvant, strlen(cuvant), sizeof(char), comparator);

    int perm = back(strlen(cuvant));

    printf("%d\n", perm);

    return 0;
}