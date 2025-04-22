/*
Se citesc dintr-un fisier transmis ca si parametru in linie de comanda, 

numerele naturale n si k (n<=26, k<=n) si apoi un alfabet format din n litere distincte.

Sa se afiseze toate parolele de cate k litere care respecta urmatoarele cerinte:

    2 litere consecutive nu pot fi egale sau vocale

    2 litere alaturate nu pot avea coduri ASCII consecutive ( nu pot exista parole 
    
    care sa contina sirurile bc sau cb de exemplu)

In cazul in care nu s-au putut crea parole, se va afisa mesajul “EROARE”.
ex:
a b c d e f g h

k=3

Solutii (partiale)
ace
acf
acg
...

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *v = NULL;

int avemSuccesor(int stiva[], int k, int n){
    if(stiva[k] < n){
        stiva[k] ++;
        return 1;
    }

    return 0;
}

int eVocala(char c){
    const char* vocale = "aeiouAEIOU";
    return strchr(vocale, c) != NULL;
}

int eValid(int stiva[], int k){
    for(int i = 1; i < k; i++){
        if(stiva[i] == stiva[k]){
            return 0;
        }

    }

  if(k > 1){
      if(stiva[k] == stiva[k - 1]){
        return 0;
    }

    if(eVocala(v[stiva[k] - 1]) && eVocala(v[stiva[k - 1] - 1])){
        return 0;
    }

    if(v[stiva[k] - 1 ] == (v[stiva[k - 1] - 1] + 1 )|| v[stiva[k] - 1] == (v[stiva[k - 1] - 1] - 1)){
        return 0;
    }
  }

    return 1;
}

int eSolutie(int stiva[], int n, int k){
    return k == n;
}

void afisare(int stiva[], int k){
    for(int i = 1; i <= k; i++){
        printf("%c", v[stiva[i] - 1]);
    }

    printf("\n");
}


int back(int n, int k2){
    int stiva[30] = {0};
    int k = 1;
    stiva[k] = 0;

    int perm = 0;

    while (k > 0)
    {
        if(avemSuccesor(stiva, k, n)){
            if(eValid(stiva, k)){
                if(eSolutie(stiva, k2, k)){
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

int main(int argc, char** argv){
    if(argc != 2){
        printf("incorrect ussage of arguments \n");
        return -1;
    }

    FILE *fin = fopen(argv[1], "r");

    if(fin == NULL){
        printf("Eroare deschidere fisier \n");
        return 1;
    }

    int n, k;

    fscanf(fin, "%d %d", &n, &k);


    v = malloc(n * sizeof(char));

    if(v == NULL){
        printf("eroare alocare memorie vector \n");
        return 2;
    }

    int i = 0;

    fgetc(fin);

    while(fscanf(fin, "%c ", &v[i++]) != EOF);

    fclose(fin);

    // for(int i = 0; i < n; i ++){
    //     printf("%c ", v[i]);
    // }

    int perm = back(n, k);

    if(perm == 0){
        printf("EROARE \n");
    }
    free(v);
    return 0;
}