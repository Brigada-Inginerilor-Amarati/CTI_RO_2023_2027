#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100  // capacitatea maximă pentru noduri

/* Matricea de adiacenţă */
static bool A[MAXN][MAXN];

/* Tabloul marcaj */
static int marc[MAXN];

/* Contorul de ordine vizitare */
static int id_counter;

/* Numărul de noduri curent */
static int N;

/* Căutare în adâncime pe matrice */
void CautaInAdancime1(int x) {
    /* 1) marchează nodul x cu următorul id */
    id_counter++;
    marc[x] = id_counter;
    printf("Vizitez nodul %d (id=%d)\n", x, id_counter);

    /* 2) pentru fiecare nod t adiacent x */
    for (int t = 0; t < N; t++) {
        if (A[x][t] && marc[t] == 0) {
            CautaInAdancime1(t);
        }
    }
}

/* Traversare completă cu apeluri DFS */
void Traversare1() {
    /* 1) resetare marcaje şi contor */
    id_counter = 0;
    for (int i = 0; i < N; i++) {
        marc[i] = 0;
    }

    /* 2) pentru fiecare nod nevizitat, porneşte DFS */
    for (int i = 0; i < N; i++) {
        if (marc[i] == 0) {
            CautaInAdancime1(i);
            printf("\n");  // separă componentele conexe
        }
    }
}

/* Construieşte un graf de test simplu */
void build_test_graph() {
    // exemplu: 7 noduri A..G => 0..6
    N = 7;
    // iniţializează matricea cu false
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = false;

    // definim arcele neorientate (bidirecţional)
    void add_edge(int u, int v) {
        A[u][v] = true;
        A[v][u] = true;
    }

    // exemplu grafic: A–B, A–C, A–F, B–D, B–E, C–E, F–G, E–G
    add_edge(0,1); // A–B
    add_edge(0,2); // A–C
    add_edge(0,5); // A–F
    add_edge(1,3); // B–D
    add_edge(1,4); // B–E
    add_edge(2,4); // C–E
    add_edge(5,6); // F–G
    add_edge(4,6); // E–G
}

int main(void) {
    build_test_graph();
    printf("DFS pe matrice de adiacență:\n");
    Traversare1();
    return 0;
}
