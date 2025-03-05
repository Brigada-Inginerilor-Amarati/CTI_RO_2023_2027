/*Pentru o grupa de studenti se dau, intr-un fisier txt cu urmatorul format,:

- pe prima linie numele si prenumele

- pe a doua linie data nasterii in formatul zi/luna/an

Folosind o structura de tip arbore binar ordonat (dupa data nasterii) sa se implementeze urmatoarele operatii:

- afisare studenti nascuti pe o anumita data

- afisare studenti nascuti inainte de o anumita data

- afisarea celui mai tanar student

- stergerea unui student localizat dupa nume

- afisarea inaltimii arborelui

- afisare studenti prin parcurgerea in inordine

- afiseaza in consola un meniu text care permite selectarea oricarei operatii din cele de mai sus*/

#include <stdio.h>
#include<stdlib.h>

typedef struct _node
{
	int day, mount, year;
	char name[100];
	struct _node *left, *right;
}Nod;
Nod *R;

Nod* init(int d, int m, int y, char c[])
{

	R = (Nod*)malloc(sizeof(Nod));
	R->day = d;
	R->mount = m;
	R->year = y;
	R->name = c;
	R->left = NULL;
	R->right = NULL;
	return R;
}
int primulNascut(Nod *N1, Nod *N2)
{
    if(N1->year < N2->year)
        return 0;
    else
    {
        if(N1->year == N2->year)
        {
            if(N1->mount < N2->mount)
            {
                return 0;
            }
            else
            {
                if(N1->mount == N2->mount)
                {
                    if(N1->day < N2->day)
                    {
                        return 0;
                    }
                    else return 1;
                }
                else return 1;
            }
        }
        else return 1;
    }
}

Nod* add(Nod *R, Nod *X)
{
	if (!primulNascut(X, R))
	{
		if (R->left == NULL)
		{
			R->left = (Nod *)malloc(sizeof(Nod));
			R->left = X;
		}
		else
		{
			add(R->left, X);
		}
	}
	else
	{
		if (R->right == NULL)
		{
			R->right = (Nod *)malloc(sizeof(Nod));
			R->right = X;
		}
		else
		{
			add(R->right, X);
		}
	}
	return R;
}
void suprima(int cheie, Nod *t, Nod* parinte)
{
	if (cheie != t->data){
		if (cheie < parinte->data)
			suprima(cheie, parinte->left, parinte);
		else
			suprima(cheie, parinte->right, parinte);
	}
	else
	{
		if (!t->left && !t->right)
		{
			Nod * p;
			p = t->left;
			for (; p->right != NULL; p = p->right)
			{
				;
			}
			t->data = p->data;
		}
		else
		{
			if (!t->left){
				t->data = t->left->data;
			}
			else
			{
				t->data = t->right->data;
			}
		}
	}
}
void Preordine(Nod *R)
{

	printf("%d ", R->data);
	if (R->left != NULL)
		Preordine(R->left);
	if (R->right != NULL)
		Preordine(R->right);
}
int main()
{
    char c[100];
    int d, m, y;
    FILE *fin = fopen("Fisier.txt", "rt");
	while(gets(c))
    {
        printf("%s\n", c);
        scanf("%d %d %d", &d, &m, &y);
    }
	return 0;
}
