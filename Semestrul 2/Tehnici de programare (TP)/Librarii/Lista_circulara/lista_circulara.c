#include "lista_circulara.h"

// Definirea structurii pentru nod
struct NODE {
    Element_t value;
    struct NODE *next_node;
};

// Funcție pentru a crea un nou nod
Node_t makeNode(Element_t data) {
    Node_t nod_creat = (Node_t)malloc(sizeof(struct NODE));
    if (nod_creat == NULL) {
        printf("Eroare alocare memorie.\n");
        return NULL;
    }
    nod_creat->value = data;
    nod_creat->next_node = NULL;
    return nod_creat;
}

// Funcție pentru a adăuga un nod la sfârșitul listei circulare
List_t append(List_t head_ref, Element_t data) {
    Node_t new_node = makeNode(data);
    if (new_node == NULL) {
        return head_ref; // În caz de eroare la alocare, nu facem nicio modificare
    }

    if (head_ref == NULL) {
        head_ref = new_node;
        new_node->next_node = head_ref;
    } else {
        Node_t temp = head_ref;
        while (temp->next_node != head_ref) {
            temp = temp->next_node;
        }
        temp->next_node = new_node;
        new_node->next_node = head_ref;
    }

    return head_ref;
}

// Funcție pentru a afișa lista circulară
void displayList(List_t head) {
    if (head == NULL) {
        printf("Lista este goală.\n");
        return;
    }
    Node_t temp = head;
    do {
        printf("%d -> ", temp->value);
        temp = temp->next_node;
    } while (temp != head);
    printf("%d (reapare la început)\n", head->value);
}

List_t deleteByValue(List_t head_ref, Element_t data) {
    if (head_ref == NULL) {
        printf("Lista este goală.\n");
        return NULL;
    }

    Node_t curr_node = head_ref;
    Node_t prev_node = NULL;

    // Căutăm nodul care conține valoarea de șters
    do {
        if (curr_node->value == data) {
            // Dacă nodul de șters este primul din listă
            if (curr_node == head_ref) {
                head_ref = curr_node->next_node;
            }

            // Legăm nodurile adiacente pentru a sări peste nodul curent
            if (prev_node != NULL) {
                prev_node->next_node = curr_node->next_node;
            }

            free(curr_node);
            return head_ref;
        }

        prev_node = curr_node;
        curr_node = curr_node->next_node;
    } while (curr_node != head_ref);

    printf("Valoarea %d nu a fost găsită în listă.\n", data);
    return head_ref;
}

// Funcție pentru a șterge un nod din listă după index
List_t deleteByIndex(List_t head_ref, int index) {
    if (head_ref == NULL) {
        printf("Lista este goală.\n");
        return NULL;
    }

    Node_t curr_node = head_ref;
    Node_t prev_node = NULL;
    int count = 0;

    // Căutăm nodul de pe poziția index
    do {
        if (count == index) {
            // Dacă nodul de șters este primul din listă
            if (curr_node == head_ref) {
                head_ref = curr_node->next_node;
            }

            // Legăm nodurile adiacente pentru a sări peste nodul curent
            if (prev_node != NULL) {
                prev_node->next_node = curr_node->next_node;
            }

            free(curr_node);
            return head_ref;
        }

        prev_node = curr_node;
        curr_node = curr_node->next_node;
        count++;
    } while (curr_node != head_ref);

    printf("Indexul %d nu a fost găsit în listă.\n", index);
    return head_ref;
}

// Funcție pentru a adăuga un nod în listă la un anumit index
List_t insertAtIndex(List_t head_ref, Element_t data, int index) {
    Node_t new_node = makeNode(data);
    if (new_node == NULL) {
        return head_ref; // În caz de eroare la alocare, nu facem nicio modificare
    }

    if (head_ref == NULL) {
        head_ref = new_node;
        new_node->next_node = head_ref;
        return head_ref;
    }

    if (index == 0) {
        new_node->next_node = head_ref;
        Node_t temp = head_ref;
        while (temp->next_node != head_ref) {
            temp = temp->next_node;
        }
        temp->next_node = new_node;
        return new_node;
    }

    Node_t curr_node = head_ref;
    int count = 0;

    // Căutăm poziția index în listă
    while (count < index - 1 && curr_node->next_node != head_ref) {
        curr_node = curr_node->next_node;
        count++;
    }

    // Inserăm noul nod după nodul de la index
    new_node->next_node = curr_node->next_node;
    curr_node->next_node = new_node;

    return head_ref;
}
