#ifndef __ARBORIB__
#define __ARBORIB__

#define N   2
#define NN  (N*2)

typedef int TipCheie;

typedef struct Nod {
    TipCheie cheie;    // nr matricol
    struct Pagina* p;  // pointer spre subarbore
    int contor;
} Nod;

typedef struct Pagina {
    int m;             // numãr de chei
    struct Pagina* p0; // pointer spre primul subarbore
    Nod e[NN + 1];     // vector de noduri (1-based)
} Pagina;

// variabile globale
extern int nr_scindari;
extern int nr_pasi_cautare;
extern int inaltime;

// funcþii B-arbore
Pagina* insereaza(Pagina* pag, TipCheie x, Nod* nod);
Pagina* suprima(Pagina* pag, TipCheie x, Nod* nod);
void afisare(Pagina* arbore, int nivel);
int cautare(Pagina* pag, TipCheie x);

// prototipul funcþiei de predcessor
TipCheie predecesor(Pagina* root, TipCheie x);

#endif // __ARBORIH__
