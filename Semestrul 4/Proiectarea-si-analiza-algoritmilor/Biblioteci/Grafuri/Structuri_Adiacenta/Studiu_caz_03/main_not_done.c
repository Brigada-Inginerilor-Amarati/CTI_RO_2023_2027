#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ----------------------------------------------------
   Tipuri de bază
   ---------------------------------------------------- */
typedef int TipAtom;    // informația stocată în nod
typedef struct NodCel* RefTipPozitie;
typedef struct ArcCel* RefListArc;

/* ----------------------------------------------------
   Celulă de listă de arce (multilistă)
   fiecare element ține pointer la nodul destinație
   ---------------------------------------------------- */
struct ArcCel {
    RefTipPozitie     nod;   // pointer la nodul destinație
    RefListArc        urm;   // următorul arc din lista de adiacență
};

/* ----------------------------------------------------
   Celulă de listă de noduri
   conține elementul, pointer la următor și cap listă arce
   ---------------------------------------------------- */
struct NodCel {
    TipAtom           data;     // informația nodului
    RefTipPozitie     urm;      // următorul nod în lista principală
    RefListArc        incep;    // capul listei de adiacență
};

/* TipGraf e doar capul listei de noduri */
typedef RefTipPozitie TipGraf;

/* TipArc ține două pointere la noduri */
typedef struct {
    RefTipPozitie     nod1, nod2;
} TipArc;

/* ----------------------------------------------------
   Creaza: graful vid
   ---------------------------------------------------- */
void Creaza(TipGraf *g) {
    *g = NULL;
}

/* ----------------------------------------------------
   Adiacent: returnează true dacă există arc p→q
   ---------------------------------------------------- */
bool Adiacent(RefTipPozitie p, RefTipPozitie q) {
    RefListArc cur = p->incep;
    while (cur) {
        if (cur->nod == q) return true;
        cur = cur->urm;
    }
    return false;
}

/* ----------------------------------------------------
   Modifica: schimbă informația p->data = a
   ---------------------------------------------------- */
void Modifica(TipAtom a, RefTipPozitie p) {
    p->data = a;
}

/* ----------------------------------------------------
   Furnizeaza: returnează p->data
   ---------------------------------------------------- */
TipAtom Furnizeaza(RefTipPozitie p) {
    return p->data;
}

/* ----------------------------------------------------
   Procedură auxiliară: șterge recursiv prima apariție
   a n în lista de arce indicată de *inceput
   ---------------------------------------------------- */
void SuprimaCel(RefTipPozitie n, RefListArc *inceput) {
    if (!*inceput) return;
    RefListArc cur = *inceput, prev = NULL;
    while (cur) {
        if (cur->nod == n) {
            if (prev) prev->urm = cur->urm;
            else      *inceput = cur->urm;
            free(cur);
            return;
        }
        prev = cur;
        cur  = cur->urm;
    }
}

/* ----------------------------------------------------
   StergeList: șterge recursiv întreaga listă de arce
   ---------------------------------------------------- */
void StergeList(RefListArc *inceput) {
    RefListArc cur = *inceput;
    while (cur) {
        RefListArc nxt = cur->urm;
        free(cur);
        cur = nxt;
    }
    *inceput = NULL;
}

/* ----------------------------------------------------
   SuprimNod: șterge toate arcele către p și apoi p însuși
   ---------------------------------------------------- */
void SuprimNod(RefTipPozitie p, TipGraf *g) {
    // 1) pentru fiecare nod din graf, șterge referința la p
    for (RefTipPozitie cur = *g; cur; cur = cur->urm) {
        if (cur != p) {
            SuprimaCel(p, &cur->incep);
        }
    }
    // 2) șterge lista de arce a lui p
    StergeList(&p->incep);
    // 3) elimină p din lista principală
    RefTipPozitie cur = *g, prev = NULL;
    while (cur) {
        if (cur == p) {
            if (prev) prev->urm = cur->urm;
            else      *g       = cur->urm;
            free(cur);
            return;
        }
        prev = cur;
        cur  = cur->urm;
    }
}

/* ----------------------------------------------------
   InserNod: adaugă p la începutul listei de noduri
   ---------------------------------------------------- */
void InserNod(RefTipPozitie *p, TipGraf *g) {
    *p = malloc(sizeof **p);
    if (!*p) { perror("malloc"); exit(EXIT_FAILURE); }
    (*p)->incep = NULL;
    (*p)->urm   = *g;
    *g         = *p;
}

/* ----------------------------------------------------
   InserArc: inserție la început în ambele liste
   ---------------------------------------------------- */
void InserArc(TipArc e, TipGraf *g) {
    // evită dubluri
    if (!Adiacent(e.nod1, e.nod2)) {
        // inserție în lista lui nod1
        RefListArc t1 = malloc(sizeof *t1);
        if (!t1) { perror("malloc"); exit(EXIT_FAILURE); }
        t1->nod = e.nod2;
        t1->urm = e.nod1->incep;
        e.nod1->incep = t1;
        // inserție în lista lui nod2
        RefListArc t2 = malloc(sizeof *t2);
        if (!t2) { perror("malloc"); exit(EXIT_FAILURE); }
        t2->nod = e.nod1;
        t2->urm = e.nod2->incep;
        e.nod2->incep = t2;
    }
}

/* ----------------------------------------------------
   SuprimArc: șterge p→q și q→p
   ---------------------------------------------------- */
void SuprimArc(TipArc e, TipGraf *g) {
    if (Adiacent(e.nod1, e.nod2)) {
        SuprimaCel(e.nod2, &e.nod1->incep);
        SuprimaCel(e.nod1, &e.nod2->incep);
    }
}

/* ----------------------------------------------------
   Exemplu de utilizare simplă
   ---------------------------------------------------- */
int main(void) {
    TipGraf g;
    Creaza(&g);

    // Inserăm nodurile a=1, b=2, c=3, d=4, e=5
    RefTipPozitie pa, pb, pc, pd, pe;
    InserNod(&pa, &g); pa->data = 1;
    InserNod(&pb, &g); pb->data = 2;
    InserNod(&pc, &g); pc->data = 3;
    InserNod(&pd, &g); pd->data = 4;
    InserNod(&pe, &g); pe->data = 5;

    // Conectăm câteva arce
    InserArc((TipArc){pa, pc}, &g);  // a–c
    InserArc((TipArc){pa, pe}, &g);  // a–e
    InserArc((TipArc){pc, pd}, &g);  // c–d

    // Verificare Adiacent(a,c)
    printf("Adiacent(a,c)? %s\n",
      Adiacent(pa, pc) ? "da" : "nu");

    // Ștergere arc a–c
    SuprimArc((TipArc){pa, pc}, &g);
    printf("După SuprimArc(a,c), Adiacent(a,c)? %s\n",
      Adiacent(pa, pc) ? "da" : "nu");

    // Ștergere nod d (4)
    SuprimNod(pd, &g);
    printf("După SuprimNod(d), Adiacent(c,d)? %s\n",
      Adiacent(pc, pd) ? "da" : "nu");

    // Eliberare memorie rămasă
    while (g) {
        RefTipPozitie tmp = g->urm;
        SuprimNod(g, &g);
        g = tmp;
    }

    return 0;
}
