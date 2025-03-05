// ARBGEN.CPP - implementarea clasei Arbore_generalizat

#include "arbgen.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void Creaza_radacina(PNod *Root,const char *nume)
// creaza nodul radacina
{
	if (*Root)
		printf("exista deja o radacina\n");
	else
	{
		*Root = (PNod)malloc(sizeof(struct Nod));
		strcpy((*Root)->Nume, nume);
		(*Root)->Frate_drept = NULL;
		(*Root)->Prim_fiu = NULL;
		(*Root)->Tata = NULL;
	}
}

char tipar[40] = "";  // folosesc la tiparirea arborelui
char * Tata(PNod root, const char *nume)
{
	PNod p;
	p=Pointer(root, nume);
	return p->Tata->Nume;
}
char * Prim_fiu(PNod root, const char *nume)
{
	PNod p;
	p = Pointer(root, nume);
	return p->Prim_fiu->Nume;
}
char * Frate_drept(PNod root, const char *nume)
{
	PNod p;
	p = Pointer(root, nume);
	return p->Frate_drept->Nume;
}
void Print(PNod p)  // tiparire in preordine
{
	printf("%s %s\n", tipar, p->Nume);
	for (PNod r = p->Prim_fiu; r; r = r->Frate_drept)
	{
		//printf("%s %s %s\n",tip1, tipar, r->Nume);
		strcat(tipar, "\t");
		Print(r);
		if (strlen(tipar)>=strlen("\t"))
			tipar[strlen(tipar) - strlen("\t")] = '\0';
	}

}
PNod Pointer(PNod root, const char * cheie_nod)
{
	PNod r1,p;
	p = root;
	if (p){
		if (!strcmp(p->Nume, cheie_nod))
			return p;
		for (PNod r = p->Prim_fiu; r; r = r->Frate_drept)
		{
			if (!strcmp(r->Nume, cheie_nod))
				return r;

			r1= Pointer(r,cheie_nod);
			if (r1) return r1;
		}
		return NULL;
	}
	return NULL;
}
void Adauga_fiu(PNod Root, const char *nume_tata, const char *nume)
{
	PNod s = NULL;
	PNod r;
	PNod p = Pointer(Root, nume_tata);
	if (p){
		s = (PNod)malloc(sizeof(struct Nod));
		strcpy(s->Nume, nume);// se creaza un nou nod
		s->Frate_drept = NULL;
		s->Prim_fiu = NULL;
		s->Tata = p;
		if (!(p->Prim_fiu))  // primul fiu
			p->Prim_fiu = s;
		else {
			for ( r = p->Prim_fiu; r->Frate_drept; r = r->Frate_drept);
			r->Frate_drept = s;  // mai exista fii, noul fiu devine ultimul
		}
	}

}
PNod Initializare_arbore(PNod Root)
{
	PNod r=NULL,p;
	if (Root)
			p = Root;
	if (p){
		for ( r = p->Prim_fiu; r; r = r->Frate_drept)
			return Initializare_arbore(r);
		free (p);
	}
	return NULL;
}
char input[100];
Arbore_generalizat arbore
int main()
{
    scanf("%s", input);
    int ok = 0;
    int i;
    char *p = input;
    printf("%s",p);
    p = strtok(input, "/");
    while(p)
    {
        if(!ok)
        {
            Creaza_radacina(&arbore, p);
            ok = 1;
        }
        p = strtok(NULL, "/");
    }

    return 0;
}
