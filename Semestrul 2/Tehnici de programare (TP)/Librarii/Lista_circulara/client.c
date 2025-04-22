#include "lista_circulara.h"

int main(void) {
    List_t head = NULL;

    // Adăugăm noduri noi
    head = append(head, 10);
    head = append(head, 20);
    head = append(head, 30);
    head = append(head, 40);

    printf("Lista circulară inițială:\n");
    displayList(head);

    // Ștergem nodul cu valoarea 20
    head = deleteByValue(head, 20);
    printf("Lista după ștergerea valorii 20:\n");
    displayList(head);

    // Ștergem nodul de la indexul 1
    head = deleteByIndex(head, 2);
    printf("Lista după ștergerea de la indexul 2:\n");
    displayList(head);

    // Inserăm un nod cu valoarea 50 la indexul 1
    head = insertAtIndex(head, 50, 0);
    printf("Lista după inserarea valorii 50 la indexul 0:\n");
    displayList(head);

    return 0;
}
