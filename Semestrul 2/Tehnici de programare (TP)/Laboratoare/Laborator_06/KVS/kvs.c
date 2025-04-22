#include <stdlib.h>
#include <stdio.h>
#include "kvs.h"


#define KVS_CAP 100
#define CHUNK 16

struct kvs{
    El_t data[KVS_CAP];
    int head;  // indexul primului element liber
};

KVS_t initKVS()
{
    KVS_t kvs = (KVS_t)malloc(sizeof(struct kvs));
    if (kvs == NULL)
    {
        perror("eroare alocare dinamica kvs");
        return NULL;
    }
    kvs->head = 0;
    return kvs;
}

KVS_t adauga(KVS_t kvs, El_t element_adaugat)
{
    if(kvs != NULL && kvs->head < KVS_CAP)
    {
        kvs->data[kvs->head] = element_adaugat;
        kvs->head++;
    }
    return kvs;
}

int comparakvs(const void *a, const void *b)
{
    const El_t *element1 = (const El_t *) a;
    const El_t *element2 = (const El_t *) b;

    if(element1->cheie > element2->cheie)
    {
        return 1;
    }
    if(element1->cheie < element2->cheie)
    {
        return - 1;
    }
    return 0;
}

int cauta(KVS_t kvs, unsigned cheie)
{
    printKVS(kvs);

    qsort(kvs->data, kvs->head, sizeof(El_t), comparakvs);

    printKVS(kvs);

    El_t cheie_cautata;
    cheie_cautata.cheie = cheie;

    El_t *rezultat = bsearch(&cheie_cautata, kvs->data, kvs->head, sizeof(El_t), comparakvs);

    //merge si &cheie fara a mai face EL_t cheie_cautata

    if (rezultat != NULL) {
        // Elementul a fost găsit, returnăm indicele
        return rezultat - kvs->data;
    } else {
        return -1;
    }
}

// int cauta(KVS_t kvs, unsigned cheie)
// {

//     printKVS(kvs);

//     qsort(kvs->data, kvs->head, sizeof(El_t), comparakvs);

//     printKVS(kvs);

//     bsearch(cheie, kvs->data, kvs->head, sizeof(El_t), comparakvs);

//     // for(int i = 0; i < kvs->head; i++)
//     // {
//     //     if(kvs->data[i].cheie == cheie)
//     //     {
//     //         return i;
//     //     }
//     // }
//     // return -1;
// }

void printKVS(KVS_t kvs)
{
    for(int i = 0; i < kvs->head; i++)
    {
        printf("Cheie: %u, Valoare: %f\n", kvs->data[i].cheie, kvs->data[i].valoare);
    }
}