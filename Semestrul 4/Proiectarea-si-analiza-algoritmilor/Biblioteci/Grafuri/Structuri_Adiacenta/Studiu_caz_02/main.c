#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ----------------------------------------------------
   Tipuri de bază
   ---------------------------------------------------- */
typedef int Key_t;
typedef int Info_t;

/* ----------------------------------------------------
   Structura element (cheie + info) pentru nodurile principale
   ---------------------------------------------------- */
typedef struct Element {
    Key_t    key;
    Info_t   info;
} Element_t;

/* ----------------------------------------------------
   Structura pentru un nod din lista de adiacență
   (stochează doar cheia vecinului)
   ---------------------------------------------------- */
typedef struct Adj {
    Key_t        key_adj;    // cheia nodului adiacent
    struct Adj  *next;       // următorul vecin
} Adj_t, *Ref_Tip_Adj_t;

/* ----------------------------------------------------
   Structura pentru un nod din lista principală de noduri
   ---------------------------------------------------- */
typedef struct Node {
    Element_t       element;         // cheie + info
    struct Node    *next_node;       // următorul nod din listă
    Ref_Tip_Adj_t   adjacency_list;  // capul listei de adiacență
} Node_t, *Ref_Tip_Node_t;

/* Graful este pur și simplu capul listei de noduri */
typedef Ref_Tip_Node_t Graph_t;

/* Pentru a reține un arc prin cei doi noduri pe care le leagă */
typedef struct {
    Ref_Tip_Node_t   node1, node2;
} Arc_t;

/* ----------------------------------------------------
   Crează un nod de adiacență care conține doar cheia vecinului
   ---------------------------------------------------- */
Ref_Tip_Adj_t crea_adj(Key_t kk) {
    Ref_Tip_Adj_t a = malloc(sizeof *a);
    if (!a) { perror("malloc"); exit(EXIT_FAILURE); }
    a->key_adj = kk;
    a->next    = NULL;
    return a;
}

/* ----------------------------------------------------
   InitGraf: creează un graf vid
   ---------------------------------------------------- */
void InitGraf(Graph_t *g) {
    *g = NULL;
}

/* ----------------------------------------------------
   CautaCheieGraf: returnează true dacă există un nod
   cu cheia k în lista principală
   ---------------------------------------------------- */
bool CautaCheieGraf(Graph_t g, Key_t k) {
    for (Ref_Tip_Node_t p = g; p; p = p->next_node)
        if (p->element.key == k)
            return true;
    return false;
}

/* ----------------------------------------------------
   IndicaNod: returnează pointerul către nodul cu cheia k
   (sau NULL dacă nu există)
   ---------------------------------------------------- */
Ref_Tip_Node_t IndicaNod(Graph_t g, Key_t k) {
    for (Ref_Tip_Node_t p = g; p; p = p->next_node)
        if (p->element.key == k)
            return p;
    return NULL;
}

/* ----------------------------------------------------
   InserNod: inserează un nod nou la începutul listei
   ---------------------------------------------------- */
void InserNod(Graph_t *g, Element_t e) {
    if (CautaCheieGraf(*g, e.key)) return;  // deja există
    Ref_Tip_Node_t nou = malloc(sizeof *nou);
    if (!nou) { perror("malloc"); exit(EXIT_FAILURE); }
    nou->element        = e;
    nou->adjacency_list = NULL;
    nou->next_node      = *g;
    *g                  = nou;
}

/* ----------------------------------------------------
   InserArc: inserează un arc neorientat k1–k2
   (afișează ambii la capul listelor lor de adiacență)
   ---------------------------------------------------- */
void InserArc(Graph_t g, Key_t k1, Key_t k2) {
    Ref_Tip_Node_t n1 = IndicaNod(g, k1);
    Ref_Tip_Node_t n2 = IndicaNod(g, k2);
    if (!n1 || !n2) return;

    // pune k2 la începutul listei lui n1
    Ref_Tip_Adj_t a1 = crea_adj(k2);
    a1->next = n1->adjacency_list;
    n1->adjacency_list = a1;

    // pune k1 la începutul listei lui n2
    Ref_Tip_Adj_t a2 = crea_adj(k1);
    a2->next = n2->adjacency_list;
    n2->adjacency_list = a2;
}

/* ----------------------------------------------------
   stergeDinLista: șterge primul nod cu cheia k dintr-o
   listă simplă de adiacență și returnează noul cap
   ---------------------------------------------------- */
static Ref_Tip_Adj_t stergeDinLista(Ref_Tip_Adj_t cap, Key_t k) {
    Ref_Tip_Adj_t prev = NULL, cur = cap;
    while (cur) {
        if (cur->key_adj == k) {
            if (prev) prev->next = cur->next;
            else       cap      = cur->next;
            free(cur);
            return cap;
        }
        prev = cur;
        cur  = cur->next;
    }
    return cap;
}

/* ----------------------------------------------------
   SuprimArc: șterge arcul dintre node1 și node2
   din ambele liste de adiacență
   ---------------------------------------------------- */
void SuprimArc(Graph_t g, Arc_t indicArc) {
    if (!indicArc.node1 || !indicArc.node2) return;
    Key_t k1 = indicArc.node1->element.key;
    Key_t k2 = indicArc.node2->element.key;
    // șterge k2 din lista lui node1
    indicArc.node1->adjacency_list =
        stergeDinLista(indicArc.node1->adjacency_list, k2);
    // șterge k1 din lista lui node2
    indicArc.node2->adjacency_list =
        stergeDinLista(indicArc.node2->adjacency_list, k1);
}

/* ----------------------------------------------------
   SuprimNod: șterge toate arcele incidente și apoi
   elimină nodul p din lista principală
   ---------------------------------------------------- */
void SuprimNod(Graph_t *g, Ref_Tip_Node_t p) {
    if (!*g || !p) return;

    // 1) șterge fiecare arc incident pe p
    while (p->adjacency_list) {
        Key_t k2 = p->adjacency_list->key_adj;
        Ref_Tip_Node_t q = IndicaNod(*g, k2);
        Arc_t a = { .node1 = p, .node2 = q };
        SuprimArc(*g, a);
    }

    // 2) elimină p din lista de noduri
    Ref_Tip_Node_t prev = NULL, cur = *g;
    while (cur) {
        if (cur == p) {
            if (prev) prev->next_node = cur->next_node;
            else      *g            = cur->next_node;
            free(cur);
            return;
        }
        prev = cur;
        cur  = cur->next_node;
    }
}

/* ----------------------------------------------------
   PrintGraf: afișează lista principală și sub‐listele
   ---------------------------------------------------- */
void PrintGraf(Graph_t g) {
    printf("Graf (liste de adiacență):\n");
    // afiseaza de la final la inceput
    for (Ref_Tip_Node_t p = g; p; p = p->next_node) {
        printf("Nod %d: ", p->element.key);
        for (Ref_Tip_Adj_t a = p->adjacency_list; a; a = a->next)
            printf("%d ", a->key_adj);
        printf("\n");
    }
}

/* ----------------------------------------------------
   Exemplu de utilizare
   ---------------------------------------------------- */
int main(void) {
    Graph_t g;
    InitGraf(&g);

    int n, m;
    printf("Introduceți numărul de noduri și arce: ");
    if (scanf("%d %d", &n, &m) != 2 || n < 0 || m < 0) {
        fprintf(stderr, "Input invalid\n");
        return EXIT_FAILURE;
    }

    // creează nodurile cu cheile 0..n-1
    for (int i = 0; i < n; i++) {
        Element_t e = { .key = i, .info = 0 };
        InserNod(&g, e);
    }

    // citește și inserează arcele
    for (int i = 0; i < m; i++) {
        int k1, k2;
        printf("Arc %d (k1 k2): ", i+1);
        if (scanf("%d %d", &k1, &k2) != 2
            || k1 < 0 || k1 >= n
            || k2 < 0 || k2 >= n) {
            fprintf(stderr, "Arc invalid\n");
            return EXIT_FAILURE;
        }
        InserArc(g, k1, k2);
    }

    // afișează graf
    PrintGraf(g);

    // exemplu de ștergere arc
    printf("\nȘterg arc %d–%d:\n", 0, 1);
    Arc_t a = { .node1 = IndicaNod(g,0), .node2 = IndicaNod(g,1) };
    SuprimArc(g, a);
    PrintGraf(g);

    // exemplu de ștergere nod
    printf("\nȘterg nod %d și arcele sale:\n", 2);
    Ref_Tip_Node_t p2 = IndicaNod(g,2);
    SuprimNod(&g, p2);
    PrintGraf(g);

    return 0;
}
