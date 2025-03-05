#include <stdio.h>
#include <stdlib.h>
#define N 100
struct nod
{
    char val[20];
    int parinte;
};
struct nod v[N];
int c=-1;
int cauta(char val[20])
{
    int i;
    for(i=0;i<=c;i++)
        if(strcmp(v[i].val,val)==0)
            return i;
    return -1;
}
void adauga(char val[20],char parinte[20])
{
    if(strcmp(val,parinte)==0)
    {
        c++;
        strcpy(v[c].val,val);
        v[c].parinte=-1;
    }
    else
    {
        int poz=cauta(parinte);
        if(poz!=-1)
        {
            c++;
            strcpy(v[c].val,val);
            v[c].parinte=poz;
        }
    }

}
void calea_cea_mai_lunga()
{
    int i,j;
    int vect[N+1];
    int maxi=0;
    for(i=0;i<=c;i++)
    {
        int poz=i,p=0;
        int aux[N+1];
        while(poz!=-1)
        {
            aux[p]=poz;
            poz=v[poz].parinte;
            p++;

        }
        if(p>maxi)
        {
            maxi=p;

            for(j=0;j<p;j++)
                vect[j]=aux[j];
        }
    }
    for(j=maxi-1;j>=0;j--)
        printf("%s ",v[vect[j]].val);
}
int main()
{   int n,i;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        char s[20];
        char b[20];
        scanf("%s",s);
        scanf("%s",b);
        adauga(s,b);
    }
    calea_cea_mai_lunga();
    return 0;
}
