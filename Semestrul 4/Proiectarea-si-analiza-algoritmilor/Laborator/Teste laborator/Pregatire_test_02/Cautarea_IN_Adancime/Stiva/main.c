#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100

/* --- structura unui nod din lista de adiacență --- */
typedef struct Nod {
    int nume;
    struct Nod *urm;
} Tip_Nod, *Ref_Tip_Nod;

/* --- graful: vector de liste de adiacență --- */
static Ref_Tip_Nod StrAdj[MAXN];
static int N;               // numărul de noduri

/* --- tabloul de marcaj și contorul de ordine --- */
static int marc[MAXN];
static int id_counter;

/* --- stivă pentru iterație --- */
static int stiva[MAXN];
static int top;

/* inițializează stiva */
void initStack() {
    top = 0;
}

/* testează dacă stiva este vidă */
bool stivVid() {
    return top == 0;
}

/* pune x în stivă */
void push(int x) {
    if (top < MAXN) {
        stiva[top++] = x;
    }
}

/* extrage (pop) și returnează vârful stivei */
int pop() {
    if (top > 0) {
        return stiva[--top];
    }
    return -1;  // stivă vidă
}

/* returnează vârful (fără a scoate) */
int varfSt() {
    if (top > 0) {
        return stiva[top-1];
    }
    return -1;
}

/* --- DFS iterativ --- */
void CautaInAdancimeNerecursiv(int start) {
    Ref_Tip_Nod t;
    // 1) punem nodul de start în stivă și colorăm gri
    initStack();
    push(start);
    marc[start] = -1;  // gri

    // 2) procesăm cât timp nu e stiva vidă
    while (!stivVid()) {
        int x = pop();
        // când extragem, marcăm negru cu id
        id_counter++;
        marc[x] = id_counter;
        printf("%d ", x);

        // parcurgem lista de adiacență a lui x
        for (t = StrAdj[x]; t; t = t->urm) {
            int y = t->nume;
            if (marc[y] == 0) {
                push(y);
                marc[y] = -1;  // gri
            }
        }
    }
}

/* --- Traversare completă --- */
void Traversare2() {
    id_counter = 0;
    // inițializare: toate albe
    for (int i = 0; i < N; i++) {
        marc[i] = 0;
    }
    // pentru fiecare componentă
    for (int x = 0; x < N; x++) {
        if (marc[x] == 0) {
            CautaInAdancimeNerecursiv(x);
            printf("\n");
        }
    }
}

/* ---Construire graf simplu--- */
void addEdge(int u, int v) {
    Ref_Tip_Nod p = malloc(sizeof *p);
    p->nume = v;
    p->urm  = StrAdj[u];
    StrAdj[u] = p;
}

int main(void) {
    // exemplu: graf neorientat cu 7 noduri 0..6
    N = 7;
    for (int i = 0; i < N; i++)
        StrAdj[i] = NULL;

    // definim arce
    // A–B, A–C, A–F, B–D, B–E, C–E, F–G, E–G
    addEdge(0,1); addEdge(1,0);
    addEdge(0,2); addEdge(2,0);
    addEdge(0,5); addEdge(5,0);
    addEdge(1,3); addEdge(3,1);
    addEdge(1,4); addEdge(4,1);
    addEdge(2,4); addEdge(4,2);
    addEdge(5,6); addEdge(6,5);
    addEdge(4,6); addEdge(6,4);

    printf("DFS iterativ:\n");
    Traversare2();

    return 0;
}
