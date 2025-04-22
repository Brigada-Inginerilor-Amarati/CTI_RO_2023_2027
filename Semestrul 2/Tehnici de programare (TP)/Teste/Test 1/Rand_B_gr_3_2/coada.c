#include <stdio.h>
#include <stdlib.h>

#include "coada.h"

struct Queue{
    Element_t *data;
    unsigned int tail;
    unsigned int head;
    unsigned int capacity;
};

PQ_t initQueue(unsigned cap)
{
    PQ_t coada;

    if((coada = malloc(sizeof(struct Queue))) == NULL)
    {
        perror("nu s-a putut aloca memorie pentru coada.\n");
        return NULL;
    }

    coada->data = malloc(cap * sizeof (Element_t));

    if(coada->data == NULL)
    {
        perror("Nu s-a putut aloca memorie pt vectoru de elemente.\n");
        exit(-1);
    }

    coada->capacity = cap;
    coada->head = 0;
    coada->tail = 0;

    return coada;
}

int compara(const void *a, const void *b)
{
    const Element_t *elem1 = (const Element_t *) a;
    const Element_t *elem2 = (const Element_t *) b;

    if (*elem1 > *elem2)
    {
        return 1;
    }
    if (*elem1 < *elem2)
    {
        return -1;
    }
    return 0;
}


StatusCode_t insereaza_element(PQ_t coada, Element_t element_inserat, int (*cond)(const void*, const void*))
{
    if(coada->tail < coada->capacity)
    {
        coada->data[coada->tail] = element_inserat;
        coada->tail++;

        qsort(coada->data, coada->tail, sizeof(Element_t), cond);
        return OK;
    }
    return Q_FULL;
}

Element_t scoate_element_vechi(PQ_t coada)
{
    Element_t auxiliar = coada->data[0];

    for(unsigned int i = 0; i < coada->tail ;i++ )
    {
        coada->data[i] = coada->data[i+1];
    }

    coada->tail --;

    return auxiliar;
}

Element_t *extrage_primele_k_elemente(PQ_t coada, unsigned int k)
{
    // Verificăm dacă coada și k sunt valide
    if (coada == NULL || k == 0) {
        fprintf(stderr, "Eroare: Parametrii invalizi.\n");
        exit(EXIT_FAILURE);
    }

    // Alocăm memorie pentru vectorul care va conține primele k elemente
    Element_t *primele_elemente = malloc(k * sizeof(Element_t));
    if (primele_elemente == NULL) {
        fprintf(stderr, "Eroare: Nu s-a putut aloca memorie.\n");
        exit(EXIT_FAILURE);
    }

    // Extragem primele k elemente din coadă și le salvăm în vector
    for (unsigned int i = 0; i < k; i++) {
        // Verificăm dacă coada este goală
        if (coada->head == coada->tail) {
            fprintf(stderr, "Eroare: Coada este goală.\n");
            free(primele_elemente);
            exit(EXIT_FAILURE);
        }
        // Extragem primul element din coadă și îl salvăm în vector
        primele_elemente[i] = scoate_element_vechi(coada);
    }

    return primele_elemente;
}

void afiseaza_coada(PQ_t coada)
{
    printf("Elementele cozii: ");
    for (unsigned int i = coada->head; i < coada->tail; i++) {
        printf("%d ", coada->data[i]);
    }
    printf("\n");
}


// int compara(unsigned a, unsigned b)
// {
//     return a-b;
// }

// StatusCode_t adauga(PQ_t coada, Element_t element_inserat, int (*cond)(unsigned, unsigned))
// {
//     if(coada->head )
// }
