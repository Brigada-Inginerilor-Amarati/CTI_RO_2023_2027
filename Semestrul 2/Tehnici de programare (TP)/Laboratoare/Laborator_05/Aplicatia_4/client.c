#include <stdio.h>
#include "queue.h"

int main() {
    printStatus();
    TEST = 7777;
    printStatus();

    Coada_t q = makeQueue();
    if (!q) {
        printf("problma la crearea cozii");
        return -1;
    }

    for (int i = 1; i <= 10; i++) {
        int x = i * 12;
        if (enqueue(q, x) != COADA_OK) {
            perror("eroare la inserarea elementului\n");
        }
        Element_t aux = 0;
        if (peekFront(q, &aux) == COADA_OK) {
            printf("Primul element din coada este %u\n", aux);
        } else {
            perror("eroare la peek\n");
        }
    }
    for (int i = 1; i <= 5; i++) {
        Element_t aux = 0;
        if (dequeue(q, &aux) == COADA_OK) {
            printf("Am scos din coada %u\n", aux);
        }
    }

    destroyQueue(q);
    return 0;
}
