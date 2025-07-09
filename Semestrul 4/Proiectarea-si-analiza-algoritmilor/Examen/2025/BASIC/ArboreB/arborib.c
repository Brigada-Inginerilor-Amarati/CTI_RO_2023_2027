#include <stdlib.h>
#include <stdio.h>
#include "arborib.h"

Nod v;
int nr_scindari = 0;
int nr_pasi_cautare = 0;

Pagina* insereaza(Pagina* pag, TipCheie x, Nod* nod)
{
	int i, s, d, mij;
	Pagina* q, * r;

	if (!nod)
	{
		v.cheie = x;
		v.contor = 1;
		v.p = NULL;
	}
	else
		v = *nod;

	if (pag == NULL) //daca nu exista radacina
	{
		pag = (Pagina*)calloc(sizeof(Pagina), 1);
		pag->e[++pag->m] = v;

		return pag;
	}

	//se cauta binar pozitia cheii x in pagina curenta
	s = 1;
	d = pag->m;
	while (s <= d)
	{
		mij = (s + d) / 2;
		if (pag->e[mij].cheie == x) //gasit
		{
			pag->e[mij].contor++;
			return pag;
		}
		if (x < pag->e[mij].cheie)
			d = mij - 1;
		else
			s = mij + 1;
	}

	//daca este pagina terminala sau daca se propaga insertia
	if (pag->p0 == NULL || nod)
	{
		if (pag->m < NN) //se poate adauga un nod in pagina curenta
		{
			++pag->m;
			for (i = pag->m; i > d + 1; i--)
				pag->e[i] = pag->e[i - 1];
			pag->e[i] = v;
		}
		//pagina curenta pag este plina => supradepasire => pagina trebuie scindata
		else
		{
			Pagina* a = pag;
			Pagina* b = (Pagina*)calloc(sizeof(Pagina), 1);
			pag = (Pagina*)calloc(sizeof(Pagina), 1);

			//scindarea paginii curente
			for (i = 1; i <= N; i++)
				b->e[i] = a->e[i + N];
			a->m = b->m = N;

			nr_scindari++;

			//cheia noudului v e cheia de scindare
			if (v.cheie > a->e[N].cheie && v.cheie < b->e[1].cheie)
				pag->e[++pag->m] = v;
			else
			{
				//ultima cheie a nodului a este folosita la scindare
				if (v.cheie < a->e[N].cheie)
				{
					pag->e[++pag->m] = a->e[N];
					for (i = a->m; i > 1 && a->e[i - 1].cheie > v.cheie; i--)
						a->e[i] = a->e[i - 1];
					a->e[i] = v;
				}
				//prima cheie a nodului a este folosita la scindare
				else
				{
					pag->e[++pag->m] = b->e[1];
					for (i = 1; i < b->m && b->e[i + 1].cheie < v.cheie; i++)
						b->e[i] = b->e[i + 1];
					b->e[i] = v;
				}
			}

			//se refac legaturile intre pagini
			b->p0 = pag->e[1].p; //prima legatura a paginii b devine legatura nodului parinte
			pag->p0 = a;         //prima legatura a nodului parinte devine fostul vecin stanga
			pag->e[1].p = b;     //a doua legatura a nodului parinte devine fostul vecin dreapta
		}
	}
	else
	{
		if (d == 0) //s-a ajuns la cel mai din stanga element => prima legatura
			q = pag->p0;
		else
			q = pag->e[d].p;
		r = insereaza(q, x, NULL);
		if (r != q) //daca pagina in care s-a inserat s-a scindat <=> arborele crescut cu un nivel
		{
			/*se incearca inserarea nodului din pagina scindata in pagina curenta
			in caz de succes, arborele nu va creste in inaltime*/
			pag = insereaza(pag, r->e[1].cheie, &r->e[1]);
			free(r); //se sterge pagina scindata, intrucat nodul a fost inserat intr-o alta pagina
		}
	}

	return pag;
}

void afisare(Pagina* arbore, int nivel)
{
	int i;

	if (!arbore)
		return;
	afisare(arbore->p0, nivel + 1);
	for (i = 1; i <= arbore->m; i++)
		afisare(arbore->e[i].p, nivel + 1);

	printf("Nivel %d: ", nivel);
	for (i = 1; i <= arbore->m; i++)
		printf("%d ", arbore->e[i].cheie);
	printf("\n");
}

int cautare(Pagina* pag, TipCheie x)
{
	nr_pasi_cautare++;
	/*Cauta cheia x in arbore. Returneaza 1 daca cheia exista, 0 daca nu exista.*/
	int s, d, mij;

	if (pag == NULL)
		return 0;

	s = 1;
	d = pag->m;
	while (s <= d) //cautare binara
	{
		//nr_pasi_cautare++;
		mij = (s + d) / 2;
		if (x == pag->e[mij].cheie)
			return 1;
		if (x < pag->e[mij].cheie)
			d = mij - 1;
		else
			s = mij + 1;
	}
	if (d == 0)
		return cautare(pag->p0, x);
	else
		return cautare(pag->e[d].p, x);
}

void vecinStang(Pagina* pag, Pagina* st, Pagina* r, int d)
{
	int i;

	if (st->m == N) //daca pagina din stanga are fix N elemente => contopire
	{
		st->e[N + 1] = pag->e[d];
		st->e[N + 1].p = r->p0;
		st->m = NN;
		for (i = N + 2; i <= NN; i++)
			st->e[i] = r->e[i - N - 1];

		for (i = d; i < pag->m; i++)
			pag->e[i] = pag->e[i + 1];
		pag->m--;
		free(r);
	}
	else //imprumut
	{
		r->m = N;
		for (i = N; i > 1; i--)
			r->e[i] = r->e[i - 1];
		r->e[1] = pag->e[d];
		r->e[1].p = r->p0;
		r->p0 = st->e[st->m].p;

		pag->e[d] = st->e[st->m];
		pag->e[d].p = r;
		st->m--;
	}
}

void vecinDrept(Pagina* pag, Pagina* dr, Pagina* r, int d)
{
	int i;

	r->e[N] = pag->e[d + 1];
	r->e[N].p = dr->p0;
	r->m = N;

	if (dr->m == N) //daca pagina din dreapta are fix N elemente => contopire
	{
		r->m = NN;
		for (i = N + 1; i <= NN; i++)
			r->e[i] = dr->e[i - N];

		for (i = 1; i < pag->m; i++)
			pag->e[i] = pag->e[i + 1];
		pag->m--;
		free(dr);
	}
	else //contopire
	{
		pag->e[d + 1] = dr->e[1];
		pag->e[d + 1].p = dr;

		dr->p0 = dr->e[1].p;
		for (i = 1; i < dr->m; i++)
			dr->e[i] = dr->e[i + 1];
		dr->m--;
	}
}

Pagina* suprima(Pagina* pag, TipCheie x, Nod* nod)
{
	int i, s, d, mij;
	Pagina* q, * r;

	//daca nu exista cheia in arbore
	if (pag == NULL || pag->m == 0)
		return NULL;

	s = 1;
	d = pag->m;
	while (s <= d) //cautare binara
	{
		mij = (s + d) / 2;
		if (x == pag->e[mij].cheie)
			break;
		if (x < pag->e[mij].cheie)
			d = mij - 1;
		else
			s = mij + 1;
	}

	/*se suprima cu ajutorul nodului, cu cheie maxima,
	mai mica decat cheia nodului curent*/
	if (x == pag->e[mij].cheie)
	{
		if (pag->p0 == NULL) //pagina curenta este pagina terminala
		{
			/*daca se elimina un nod dintr-o pagina neterminala,
			se schimba continutul nodurilor, dar se pastreaza legatura*/
			if (nod)
			{
				q = nod->p;
				*nod = pag->e[pag->m];
				nod->p = q;
			}
			for (i = mij; i < pag->m; i++)
				pag->e[i] = pag->e[i + 1];
			pag->m--;

			//pagina terminala curenta s-a golit => arborele scade in inaltime
			//posibil doar pentru N == 1
			for (q = pag; pag && pag->m == 0; free(q), q = pag)
				pag = pag->p0;

			return pag;
		}
		/*dupa mutarea cheii intr-o pagina terminala,
		se trece la eliminarea ei, prin repetarea pasului curent;
		se presupune ca cheia de sters este mai mica cu o unitate*/
		return suprima(pag, x - 1, &pag->e[mij]);
	}

	if (d == 0)
		q = pag->p0;
	else
		q = pag->e[d].p;
	r = suprima(q, x, nod); //se incearca eliminarea cheii din subarborele corespunzator

	//conditia (r == NULL) garanteaza ca este pagina terminala
	/*daca nu exista cheia aleasa sa inlocuiasca cheia de sters
	se repeta pasul de stergere folosind cheia cu cea mai mare valoare*/
	if (r == NULL)
	{
		if (nod)
			return suprima(pag, pag->e[d].cheie, nod);
		else //daca nu exista cheia in subarbore
			return pag;
	}

	if (r->m < N) //subdepasire => imprumut sau contopire
	{
		Pagina* st, * dr;
		if (d == 1)
			st = pag->p0;
		else
			st = pag->e[d - 1].p;
		dr = pag->e[d + 1].p;

		if (r == pag->p0) //cel mai din stanga nod
			vecinDrept(pag, dr, r, d);
		else if (d == pag->m) //cel mai din dreapta nod
			vecinStang(pag, st, r, d);
		else //are 2 vecini
		{
			/*
			se imprumuta de la vecinul cu nr maxim de noduri in pagina sau se contopesc 2 pagini;
			cum nu pot exista simultan 2 pagini cu mai putin de N elemente =>
			oricare pagina poate fi aleasa pentru contopire, daca este cazul
			*/

			//se imprumuta de la vecinul drept
			if (dr->m > st->m)
				vecinDrept(pag, dr, r, d);
			//se imprumuta (sau contopeste) de la (cu) vecinul stang
			else
				vecinStang(pag, st, r, d);
		}
	}

	//radacina subarborelui curent s-a golit => arborele scade in inaltime
	for (q = pag; pag && pag->m == 0; free(q), q = pag)
		pag = pag->p0;

	return pag;
}

// functie care primind nr matricol returneaza nr matricol imd mai mic valoric din serie

TipCheie predecesor(Pagina* root, TipCheie x) {
	TipCheie pred = -1;
	Pagina* p = root;

	while (p) {
		int s = 1, d = p->m, mij;

		// 1) Căutăm x în această pagină
		while (s <= d) {
			mij = (s + d) / 2;
			if (p->e[mij].cheie == x) {
				// Găsit exact: trebuie să coborâm în SUBARBORELE STÂNG
				// al poziției mij, adică:
				//   - dacă mij==1 → p0
				//   - altfel → e[mij-1].p
				Pagina* q = (mij == 1 ? p->p0 : p->e[mij - 1].p);
				if (!q)
					return pred;     // nu are stânga → ne întoarcem la candidatul acumulat
				// mergem până la dreapta maximă
				while (q->p0) {
					q = q->e[q->m].p;
				}
				// în ultima pagină vizitată, cheia de pe ultima poziție e pred.
				return q->e[q->m].cheie;
			}
			if (x < p->e[mij].cheie) {
				d = mij - 1;
			}
			else {
				// p->e[mij].cheie < x, așadar e posibil candidat
				if (p->e[mij].cheie > pred)
					pred = p->e[mij].cheie;
				s = mij + 1;
			}
		}

		// 2) Dacă n-am găsit în pagină → coborâm în copilul corespunzător lui d
		if (d <= 0)
			p = p->p0;
		else
			p = p->e[d].p;
	}

	return pred;
}
