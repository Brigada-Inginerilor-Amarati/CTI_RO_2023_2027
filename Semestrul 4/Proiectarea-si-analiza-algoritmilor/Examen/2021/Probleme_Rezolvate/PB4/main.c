#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct student
{

    char nume[30];
    char email[30];
};
struct stud
{
    struct student v[100];
    int c;
};
struct arb
{   int id;
    char curs[30];
    char prof[30];
    struct arb *stang;
    struct arb *drept;
    struct stud s;
};

struct arb* neww(int id,char curs[30],char prof[30],struct arb *stang, struct arb *drept)
{
    struct arb * n=(struct arb *)malloc(sizeof(struct arb));
    if(!n)
    {
        printf("eroare la alocare");
        exit(EXIT_FAILURE);
    }
    n->id=id;
    strcpy(n->curs,curs);
    strcpy(n->prof,prof);
    n->drept=drept;
    n->stang=stang;
    n->s.c=-1;
    return n;

}


struct arb *add(int id,char curs[30],char prof[30],struct arb *arb)
{
    if(! arb)
        return neww(id,curs,prof,NULL,NULL);
   else{
    struct arb *n;
    struct arb *aux,*prev=NULL;
    n=neww(id,curs,prof,NULL,NULL);
    aux=arb;
    while(aux!=NULL)
    {   prev=aux;
        if(aux->id>id )
        aux=aux->stang;
        else
        aux=aux->drept;

    }
    if(id<prev->id)
        prev->stang=n;
    else
        prev->drept=n;
    return arb;}

}
struct lista
{
    int id;
    char curs[30];
    char prof[30];
    struct stud s;
    struct lista * next;
};
struct lista * nou(int id, char curs[30],char prof[30],struct stud s,struct lista *next)
{

struct lista * n=(struct lista *)malloc(sizeof(struct lista));
    if(!n)
    {
        printf("eroare la alocare");
        exit(EXIT_FAILURE);
    }
    n->id=id;
    strcpy(n->curs,curs);
    strcpy(n->prof,prof);
    n->next=next;

    n->s=s;
    return n;
};
struct lista *addLista(int id, char curs[30],char prof[30],struct stud s,struct lista *l)
{
    if(!l)
        return nou(id,curs,prof,s,NULL);
    struct lista *aux=l;
    struct lista *n=nou(id,curs,prof,s,NULL);
    while(aux->next)
    {
        aux=aux->next;
    }
    aux->next=n;
    return l;

};
struct lista * cursuriOrdonateDupaID(struct arb * r,struct lista *l)
{
      if(r)
    {


        l=cursuriOrdonateDupaID(r->stang,l);
        l=addLista(r->id,r->curs,r->prof,r->s,l);
        l=cursuriOrdonateDupaID(r->drept,l);

    }
    else return l;



};
void afisare(struct lista *l)
{
    while(l)
    {
        printf("%d ",l->id);
        l=l->next;
    }
}
int main()
{
    struct arb *arb=NULL;
    int n,i;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        char s[30];
        int id;
        char c[30];
        scanf("%s %d %s",s,&id,c);
        arb=add(id,c,s,arb);
    }
     struct lista *l=NULL;
    l=cursuriOrdonateDupaID(arb,l);
    afisare(l);
    return 0;
}
