#include <stdio.h>
#include <stdlib.h>
#include "arborib.h"

int main(int argc, char **argv) {
    Pagina* arbore = NULL;
    FILE* f = fopen(argv[1], "r");
    if (!f) {
        perror("students.txt");
        return 1;
    }

    TipCheie mat;
    int an;
    while (fscanf(f, "%d %d", &mat, &an) == 2) {
        arbore = insereaza(arbore, mat, NULL);
    }
    fclose(f);

    // afișăm B-arborele
    printf("Structura B-arborelui după inserare:\n");
	afisare(arbore, 0);

    // citim x de la utilizator
    printf("\nIntroduceți un număr matricol x: ");
    if (scanf("%d", &mat) != 1) return 0;

    TipCheie pre = predecesor(arbore, mat);
    if (pre < 0)
        printf("Nu există niciun nr. matricol < %d în arbore.\n", mat);
    else
        printf("Predecesorul lui %d în arbore este %d.\n", mat, pre);

    return 0;
}
