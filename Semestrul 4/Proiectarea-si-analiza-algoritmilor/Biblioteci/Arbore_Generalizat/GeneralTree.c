#include "GeneralTree.h"

TipNod creeazaNod(TipCheie valoare, ArboreGeneral arbore1, ArboreGeneral arbore2) {
	TipNod nod = (TipNod)malloc(sizeof(Nod_t));


	// caz gestionat in main
	if (!nod) {
		printf("Eroare la alocare\n");
		return NULL;
	}

	nod->cheie = valoare;
	nod->primulFiu = arbore1;
	nod->frateDreapta = arbore2;

	return nod;
}



