#include <stdio.h>
#include <stdlib.h>
#define N 2
#define NN 4
struct Nod
{

    int cheie;//id
    int an_nastere;
    int vaccinat;
    struct Pagina *p;
    int contor;

};
struct Pacient
{
    int cheie;//id
    int an_nastere;
    int vaccinat;
    struct Pacient *next;
};
struct Pacient* aloc(int cheie,int an_nastere, int vaccinat, struct Pacient*next)
{
    struct Pacient p=(struct Pacient)malloc(sizeof(struct Pacient));
    if(!p)
    {
        printf("eroare la alocare");
        exit(EXIT_FAILURE);
    }
    p->an_nastere=an_nastere;
    p->cheie=cheie;
    p->vaccinat=vaccinat;
    p->next=next;
    return p;
}
struct Pacient*add(int cheie,int an_nastere, int vaccinat, struct Pacient* pa)
{

    if(pa==NULL)
     return aloc(cheie,an_nastere,vaccinat,NULL);
    struct Pacient * aux,*x;
    aux=pa;
    x=aloc(cheie,an_nastere,vaccinat,NULL);
    while(aux->next)
    {
        aux=aux->next;
    }
    aux->next=x;
    return pa;

};
struct Pagina
{
    struct Pagina *p0;
    int m;
    struct Nod e[NN+1];
};
struct Nod v;
struct Pagina* insereaza(struct Pagina *pag, int x,int an_nastere,int vaccinat, struct Nod *nod)
{
	int i, s, d, mij;
	struct Pagina *q, *r;

	if (!nod)
	{
		v.cheie= x;
		v.an_nastere=an_nastere;
		v.vaccinat=vaccinat;
		v.contor = 1;
		v.p = NULL;
	}
	else
		v = *nod;

	if (pag == NULL) //daca nu exista radacina
	{
		pag = (struct Pagina*)calloc(sizeof(struct Pagina), 1);
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
			struct Pagina *a = pag;
			struct Pagina b = (struct Pagina)calloc(sizeof(struct Pagina), 1);
			pag = (struct Pagina*)calloc(sizeof(struct Pagina), 1);

			//scindarea paginii curente
			for (i = 1; i <= N; i++)
				b->e[i] = a->e[i + N];
			a->m = b->m = N;

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
		r = insereaza(q, x,an_nastere,vaccinat, NULL);
		if (r != q) //daca pagina in care s-a inserat s-a scindat <=> arborele crescut cu un nivel
		{
			/*se incearca inserarea nodului din pagina scindata in pagina curenta
			in caz de succes, arborele nu va creste in inaltime*/
			pag = insereaza(pag, r->e[1].cheie,r->e[1].an_nastere,r->e[1].vaccinat ,&r->e[1]);
			free(r); //se sterge pagina scindata, intrucat nodul a fost inserat intr-o alta pagina
		}
	}

	return pag;
}
struct Pagina *head;
struct Pacient * afisare(struct Pagina *p,struct Pacient *pa)
{  int i;
    if(p)
    {   for(i=1;i<=p->m;i++)
            if(p->e[i].an_nastere<2000 && p->e[i].vaccinat==0)
                pa=add(p->e[i].cheie,p->e[i].an_nastere,p->e[i].vaccinat,pa);

        pa=afisare(p->p0,pa);
        for(i=1;i<=p->m;i++)
             pa=afisare(p->e[i].p,pa);

    }

        return pa;
}
struct Pacient *pac;
int main()
{
    int n,i;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        int id,an,vacc;
        scanf("%d %d %d",&id,&an,&vacc);
        head=insereaza(head,id,an,vacc,NULL);

    }

    pac=afisare(head,pac);
    while(pac)
    {
        printf("%d ",pac->cheie);
        pac=pac->next;
    }
    return 0;
}
