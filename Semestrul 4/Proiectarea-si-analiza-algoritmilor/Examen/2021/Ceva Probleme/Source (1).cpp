//va rog sa imi verificati programul;

#include <iostream>

using namespace std;

#define N 2
#define NN 2 * N

typedef struct Pagina* ref;

struct Nod_B {
	int cheie;
	struct Pagina *p; //pagina cu chei mai mari decat cheia curenta
	int contor;
};

struct Pagina {
	int m;              //valori [n, nn]
	struct Pagina *p0;  //pagina cu chei mai mici decat in pagina curenta
	struct Nod_B e[NN + 1]; //cheile paginii curente si
	//pointeriispre cele descendente
};

void tiparb_B(struct Pagina *p, int l)
{
	int i;
	if (p != NULL)
	{
		for (i = 0; i < p->m; i++)
			cout<<p->e[i].cheie<<" ";
		cout << endl;

		tiparb_B(p->p0, l + 1);

		for (i = 0; i < p->m; i++)
			tiparb_B(p->e[i].p, l + 1);
	}
}
int s;
void medie(struct Pagina *p, int l) {
	int i;
	if (p != NULL)
	{
		for (i = 0; i < p->m; i++)
			s+= p->e[i].cheie;
		
		medie(p->p0, l + 1);

		for (i = 0; i < p->m; i++)
			medie(p->e[i].p, l + 1);
	}
}

int main() {
	Nod_B *q = new Nod_B();
	q->cheie = 11;
	q->p = NULL;
	Nod_B *q1 = new Nod_B();
	q1->cheie = 21;
	q1->p = NULL;
	Nod_B *q2 = new Nod_B();
	q2->cheie = 31;
	q2->p = NULL;
	Nod_B *q3 = new Nod_B();
	q3->cheie = 41;
	q3->p = NULL;
	Nod_B *q4 = new Nod_B();
	q4->cheie = 15;
	q4->p = NULL;
	Pagina *p = new Pagina();
	p->e[0] = *q;
	p->e[1] = *q4;
	p->e[2] = *q1;
	p->e[3] = *q2;
	p->m = 4;
	Pagina *pp = new Pagina();
	pp->e[0] = *q3;
	p->p0 = pp;
	pp->m = 1;
	tiparb_B(p, NN);
	medie(p, NN);
	float y = NN;
	float medie = s / y;
	cout << endl << "Media este:" <<(float) medie<<endl;
	system("pause");
}