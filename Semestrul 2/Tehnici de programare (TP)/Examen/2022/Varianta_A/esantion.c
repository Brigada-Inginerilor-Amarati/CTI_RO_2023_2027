#include "esantion.h"

struct LOCATIE{
    int grade;
    int minute;
    int secunde;
};

struct ESANTION{
    double valoare_masurata;

    int ora_masurarii;

    Locatie_t locatie;

    char comentarii[MAX_LEN];
};

Esantion_t makeEsantion(double value, int ora, int grd, int min, int sec, const char *comm){
    Esantion_t esantion = malloc(sizeof(struct ESANTION));

    if(esantion == NULL){
        printf("eroare la alocare memorie esantion.\n");
        return NULL;
    }

    esantion->valoare_masurata = value;
    esantion->ora_masurarii = ora;

    esantion->locatie = malloc(sizeof(struct LOCATIE));

    if(esantion->locatie == NULL){
        free(esantion);
        return NULL;
    }

    esantion->locatie->grade = grd;
    esantion->locatie->minute = min;
    esantion->locatie->secunde = sec;

    strncpy(esantion->comentarii, comm, MAX_LEN - 1);
    esantion->comentarii[MAX_LEN - 1] = 0;

    return esantion;
}

Esantion_t* addSample(Esantion_t *t, int *n, Esantion_t e){
    t = realloc(t, ((*n) + 1) * sizeof(Esantion_t));

    if(t == NULL){
        return NULL;
    }

    t[*n] = e;
    (*n) ++;

    return t;
}

Esantion_t getMaxTemp(Esantion_t *esantioane, int n){
    Esantion_t maxim = esantioane[0];

    for(int i = 1; i < n; i++){
        if(esantioane[i]->valoare_masurata > maxim->valoare_masurata){
            maxim = esantioane[i];
        }
    }

    return maxim;
}

Esantion_t *copySamples(Esantion_t v[], int n, double tMin, double tMax, int *size){
    Esantion_t *rezultat = NULL;
    int count = 0;

    for(int i = 0; i < n; i++){
        if(v[i]->valoare_masurata >= tMin && v[i]->valoare_masurata <= tMax){
            Esantion_t *aux = realloc(rezultat, (count + 1) * sizeof(Esantion_t));

            if(aux == NULL){
                printf("eroare la realocare memorie\n");
                free(aux);
                return rezultat;
            }

            rezultat = aux;

            rezultat[count++] = v[i];
        }
    }

    Esantion_t *aux = realloc(rezultat, (count + 1) * sizeof(Esantion_t));

    if(aux == NULL){
        printf("eroare la realocare memorie\n");
        free(aux);
        return rezultat;
        } 

    rezultat = aux;
    Esantion_t end = makeEsantion(0, 0, 0, 0, 0, "");
    rezultat[count++] = end;

    (*size) = count;

    return rezultat;
}

void printEsantion(Esantion_t esantion){
    if(esantion){
        printf("Valoare : %.2f - Ora : % d - Locatie : %d*%d'%d\" - Comentarii : %s \n", 
        esantion->valoare_masurata, esantion->ora_masurarii,
        esantion->locatie->grade, esantion->locatie->minute, esantion->locatie->secunde,
        esantion->comentarii);
    }
}

void printEsantioante(Esantion_t *esantioane, int n){
    if(esantioane){
        for(int i = 0; i < n; i++){
            printEsantion(esantioane[i]);
        }
        printf("\n");
    }
}

void freeEsantion(Esantion_t esantion){
    if(esantion){
        free(esantion->locatie);
        free(esantion);
    }
}

void freeEsantioane(Esantion_t *esantioane, int n){
    for(int i = 0; i < n; i++){
        freeEsantion(esantioane[i]);
    }
    
    free(esantioane);
}

void freeEsantioanefiltrate(Esantion_t *p, int size){
    free(p[size - 1]->locatie);
    free(p[size - 1]);
    free(p);
}