//1.Pentru o serie de studenti, se cunosc numele,prenumele si anul nasterii. Considerand ca pentru stocarea datelor despre studenti se foloseste o
//structura de tip arbore binar ordonat, sa se scrie o functie care determina daca are inaltimea minima.
#include <iostream>
#define H 5
#define N 2*H-1

using namespace std;

struct Nod {
	int inf;
	Nod *stang, *drept;
};

Nod *rad;

Nod *creareNod(int x) {
	Nod *nou;
	nou = new Nod();
	if (nou == NULL) {
		cout << "Nu s-a creat nodul";
		return NULL;
	}
	nou->inf = x;
	nou->stang = NULL;
	nou->drept = NULL;
	//cout << nou->inf << " ";
	return nou;
}
Nod *inserareNod(Nod *prim, int x)
{
	 Nod *nod_nou, *nod_curent, *nod_parinte = NULL;

	nod_nou = creareNod(x);

	if (prim == NULL)
	{
		/* arborele este vid */
		prim = nod_nou;
		printf("A fost adaugat primul nod: %d. \n", prim->inf);
		return prim;
	}
	else
	{
		/* pozitionare in arbore pe parintele nodului nou */
		nod_curent = prim;

		while (nod_curent != NULL)
		{
			nod_parinte = nod_curent;

			if (x < nod_curent->inf) /* parcurgere spre stanga */
				nod_curent = nod_curent->stang;
			else /* parcurgere spre dreapta */
				nod_curent = nod_curent->drept;
		}

		/* creare legatura nod parinte cu nodul nou */
		if (x < nod_parinte->inf)
		{
			/* se insereaza la stanga nodului parinte */
			nod_parinte->stang = nod_nou;
			printf("Nodul %d a fost inserat la stanga nodului %d. \n",
				x, nod_parinte->inf);
		}

		else
		{
			/* se insereaza la dreapta nodului parinte */
			nod_parinte->drept = nod_nou;
			printf("Nodul %d a fost inserat la dreapta nodului %d.\n",
				x, nod_parinte->inf);
		}

		return prim;
	}
}


/* parcurgere arbore in preordine */
void afisare_preordine(Nod *prim)
{
	if (prim != NULL)
	{
		/* parcurgere radacina, stanga, dreapta */
		cout << prim->inf << " ";
		afisare_preordine(prim->stang);
		afisare_preordine(prim->drept);
	}
}
void afisare_postordine(Nod *prim)
{
	if (prim != NULL)
	{
		/* parcurgere radacina, stanga, dreapta */
		afisare_postordine (prim->stang);
		afisare_postordine(prim->drept);
		cout << prim->inf << " ";
	}
}
void afisare_inordine(Nod *prim)
{
	if (prim != NULL)
	{
		/* parcurgere radacina, stanga, dreapta */
		afisare_inordine(prim->stang);
		cout << prim->inf << " ";
		afisare_inordine(prim->drept);
	}
}

int inaltime(Nod *rad) {
	int st = 0, dr=0; 
	if (rad == NULL) return 0;
	else {
		st = inaltime(rad->stang);
		dr = inaltime(rad->drept);
		if (st > dr || st == dr) 
			return st + 1;
		return dr + 1;
	}
}

Nod *cautaNod(Nod *rad, int x) {
	if (rad != NULL) {
		if (x == rad->inf) return rad;
		else if (x < rad->inf) cautaNod(rad->stang, x);
		else cautaNod(rad->drept, x);
	}
	else return NULL;
}

/*
stergere arbore/subarbore */

Nod *stergereArb(Nod *plecare) {
	if (plecare != NULL) {
		stergereArb(plecare->stang);
		stergereArb(plecare->drept);
		free(plecare);
	}
	return NULL;
}

int main() {
	rad = inserareNod(rad, 1);
	rad = inserareNod(rad, 9);
	rad = inserareNod(rad, 8);
	rad = inserareNod(rad, 5);
	rad = inserareNod(rad, 3);
	rad = inserareNod(rad, 4);
	rad = inserareNod(rad, 6);
	rad = inserareNod(rad, 2);
	rad = inserareNod(rad, 7);
	cout << "Preordine: ";
	afisare_preordine(rad);
	cout << endl<<"Inordine: ";
	afisare_inordine(rad);
	cout << endl<<"Postordine: ";
	afisare_postordine(rad);
	cout << endl;
	cout << "Inaltimea arborelui: " << inaltime(rad);
	cout << endl;
	Nod *t1 = cautaNod(rad, 3),*t2 = cautaNod(rad, 6);
		
	t1->stang = stergereArb(t1->stang);
	t1->drept = stergereArb(t1->drept);
	t2->stang = stergereArb(t2->stang);
	t2->drept = stergereArb(t2->drept);
	cout << "Inordine: ";
	afisare_inordine(rad);

	cout << endl;
	system("pause");
}