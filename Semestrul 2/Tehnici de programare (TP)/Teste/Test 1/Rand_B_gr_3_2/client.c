#include <stdio.h>
#include <stdlib.h>
#include "coada.h"

int main(void)
{
    unsigned int capacitate = 5;
    PQ_t coada = initQueue(capacitate);

    // Verificăm dacă coada a fost inițializată corect
    if (coada == NULL) {
        fprintf(stderr, "Eroare la inițializarea cozii\n");
        return EXIT_FAILURE;
    }

    // Inserăm elemente în coadă
    insereaza_element(coada, 5, compara);
    insereaza_element(coada, 3, compara);
    insereaza_element(coada, 8, compara);
    insereaza_element(coada, 2, compara);
    insereaza_element(coada, 7, compara);
    insereaza_element(coada, 9, compara);
    insereaza_element(coada, 1, compara);
    insereaza_element(coada, 0, compara);

    afiseaza_coada(coada);


    // Scoatem un element din coadă
    Element_t element_scos = scoate_element_vechi(coada);
    printf("Elementul scos din coadă: %d\n", element_scos);

    afiseaza_coada(coada);

    unsigned int k = 2;
    Element_t *primele_k_elemente = extrage_primele_k_elemente(coada, k);

    // Afisam primele k elemente extrase si le eliberam memoria
    printf("Primele %d elemente extrase: ", k);
    for (unsigned int i = 0; i < k; i++) {
        printf("%d ", primele_k_elemente[i]);
    }
    printf("\n");

    afiseaza_coada(coada);

    // Eliberăm memoria alocată pentru vectorul de elemente
    free(primele_k_elemente);


    return EXIT_SUCCESS;
}
