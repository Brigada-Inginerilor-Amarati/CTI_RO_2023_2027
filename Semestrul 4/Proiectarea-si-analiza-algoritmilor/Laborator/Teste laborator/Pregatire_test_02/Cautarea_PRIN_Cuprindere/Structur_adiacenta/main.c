#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100

/* --- nod în lista de adiacență --- */
typedef struct Nod {
    int nume;
    struct Nod *urm;
} Tip_Nod, *Ref_Tip_Nod;

/* --- graful: vector de liste de adiacență --- */
static Ref_Tip_Nod StrAdj[MAXN];
static int N;  // numărul de noduri

/* --- marcaje și contor pentru BFS iterative --- */
static int marc[MAXN];
static int id_counter;

/* --- coadă FIFO simplă --- */
typedef struct {
    int data[MAXN];
    int front, rear;
} Queue_t;

static Queue_t Q;

void initQueue() {
    Q.front = Q.rear = -1;
}

bool isEmpty() {
    return Q.front == -1;
}

void enqueue(int x) {
    if (Q.rear == MAXN - 1) return;
    if (isEmpty()) Q.front = 0;
    Q.data[++Q.rear] = x;
}

int dequeue() {
    if (isEmpty()) return -1;
    int v = Q.data[Q.front++];
    if (Q.front > Q.rear) Q.front = Q.rear = -1;
    return v;
}

/* --- BFS iterativ (varianta 10.4.2.2.a) --- */
void CautaPrinCuprindere(int start) {
    Ref_Tip_Nod t;
    initQueue();
    id_counter = id_counter; // contor e global

    /* amorsare: enqueu start, marchez gri (-1) */
    enqueue(start);
    marc[start] = -1;

    /* repetă până coada e vidă */
    while (!isEmpty()) {
        int x = dequeue();
        /* procesare nod x: vizitat complet => id */
        id_counter++;
        marc[x] = id_counter;
        printf("%d ", x);

        /* enqueu toți vecinii nevizitați */
        for (t = StrAdj[x]; t; t = t->urm) {
            int y = t->nume;
            if (marc[y] == 0) {
                enqueue(y);
                marc[y] = -1;
            }
        }
    }
}

/* --- Traversare completă --- */
void ParcurgerePrinCuprindere() {
    id_counter = 0;
    /* inițializare: alb (0) pentru toate nodurile */
    for (int x = 0; x < N; x++) {
        marc[x] = 0;
    }
    /* pentru fiecare componentă conexă */
    for (int x = 0; x < N; x++) {
        if (marc[x] == 0) {
            CautaPrinCuprindere(x);
            printf("\n");  // delimitare componente
        }
    }
}

/* --- adaugă muchie neorientată --- */
void addEdge(int u, int v) {
    Ref_Tip_Nod p = malloc(sizeof *p);
    p->nume = v;
    p->urm  = StrAdj[u];
    StrAdj[u] = p;
    p = malloc(sizeof *p);
    p->nume = u;
    p->urm  = StrAdj[v];
    StrAdj[v] = p;
}

/* --- exemplu de utilizare --- */
int main(void) {
    // inițializare graf simplu cu 7 noduri 0..6
    N = 7;
    for (int i = 0; i < N; i++)
        StrAdj[i] = NULL;

    // definirea arcelor
    addEdge(0, 5); // A–F
    addEdge(0, 2); // A–C
    addEdge(0, 1); // A–B
    addEdge(0, 6); // A–G
    addEdge(5, 0); // F–A redundanta e neorientat deja
    addEdge(5, 4); // F–E
    addEdge(5, 3); // F–D
    addEdge(2, 0); // C–A
    addEdge(1, 0); // B–A
    addEdge(6, 4); // G–E
    addEdge(6, 0); // G–A
    addEdge(3, 5); // D–F
    addEdge(4, 5); // E–F
    addEdge(4, 6); // E–G
    // componente separate H-I-J-K și L-M
    addEdge(7,8); addEdge(7,9); addEdge(7,10);
    addEdge(8,7); addEdge(9,7); addEdge(10,7);
    addEdge(8,9); addEdge(9,8);
    addEdge(9,10); addEdge(10,9);
    addEdge(11,12); addEdge(11,13);
    addEdge(12,11); addEdge(13,11);

    printf("BFS iterative cu marc și id:\n");
    ParcurgerePrinCuprindere();
    return 0;
}
