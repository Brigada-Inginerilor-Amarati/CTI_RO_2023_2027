#ifndef __GENERALTREE_H
#define __GENERALTREE_H

#include <stdio.h>
#include <stdlib.h>

// definim TDA arbore general

typedef struct Nod {
	int cheie;
	struct Nod* primulFiu;
	struct Nod* frateDreapta;
}Nod_t;

// pointer la o structura de tip Nod_t
typedef Nod_t* TipNod;

// definim un arbore general
typedef TipNod ArboreGeneral;

typedef int TipCheie;

// functii pentru arbore general

// creare nod

TipNod creeazaNod(TipCheie valoare, ArboreGeneral arbore1, ArboreGeneral arbore2);

// initializare arbore

ArboreGeneral initializareArbore();

// inserare nod

ArboreGeneral inserareNod(ArboreGeneral arbore, TipCheie valoare, TipCheie parinte);

#endif 
