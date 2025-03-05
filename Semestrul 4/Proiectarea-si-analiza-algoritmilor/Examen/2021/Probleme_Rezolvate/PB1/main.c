#include <stdio.h>
#include <stdlib.h>
#define N 100
struct nod
{   char nume[20];
    int fd;
    int pf;
};
struct arb
{
    struct nod nod[N+1];
    int cursor;
};
//int c=0;
struct arb arb;
/*int cauta(int cheie)
{   int i;
    for(i=0;i<c;i++)
    {

        if(arbore[i].valoare==cheie)
            return i;
    }
    return -1;
}
void adauga(char nume[20])
{
    strcpy(arb.nod[c],nume);


}*/
int vizitat[N];
int nivv;
int max;
void nivele(int x,int niv)
{



                if(arb.nod[x].pf!=-1)
                {
                    nivele(arb.nod[x].pf,niv+1);


                }

                if(arb.nod[x].fd!=-1)
                {


                     nivele(arb.nod[x].fd,niv);


                }
                vizitat[x]=niv;
                if(max<niv)
                    max=niv;






}
void count_nivele()
{  int i,j;
    for(i=1;i<=max;i++)
    {
        int cont=0;
        for(j=0;j<arb.cursor;j++)
            if(vizitat[j]==i)
            cont++;
        printf("%d\n",cont);
    }

}


int main()
{     /*arb.nod[0].pf=1;
      arb.nod[0].fd=-1;
      strcpy(arb.nod[0].nume,"7");
      arb.nod[1].pf=-1;
      arb.nod[1].fd=2;
      strcpy(arb.nod[1].nume,"6");
      arb.nod[2].pf=3;
      arb.nod[2].fd=-1;
      strcpy(arb.nod[2].nume,"C2");
      arb.nod[3].pf=4;
      arb.nod[3].fd=-1;
      strcpy(arb.nod[3].nume,"C2'");
      arb.nod[4].pf=-1;
      arb.nod[4].fd=-1;
      strcpy(arb.nod[4].nume,"C2''");*/

      /*int h1=1,h2=1;
      inaltimemax(0,&h1,&h2,1);
      if(h1>h2)
      printf("%d",h1);
      else
      printf("%d",h2);*/
arb.nod[0].pf=1;
arb.nod[0].fd=-1;
      strcpy(arb.nod[0].nume,"C");
      arb.nod[1].pf=2;
      arb.nod[1].fd=3;
      strcpy(arb.nod[1].nume,"C1");
      arb.nod[2].pf=-1;
      arb.nod[2].fd=-1;
      strcpy(arb.nod[2].nume,"C2");
      arb.nod[3].pf=4;
      arb.nod[3].fd=-1;
      strcpy(arb.nod[3].nume,"C2'");
    arb.nod[4].pf=6;
      arb.nod[4].fd=5;
      strcpy(arb.nod[4].nume,"C2'");

      arb.nod[5].pf=-1;
      arb.nod[5].fd=-1;
      strcpy(arb.nod[6].nume,"C2'");
      arb.nod[6].pf=-1;
      arb.nod[6].fd=-1;
      strcpy(arb.nod[6].nume,"C2'");
      int h1=1,h2=1;
      nivele(0,h1);
      arb.cursor=7;

      count_nivele();
      return 0;
}
