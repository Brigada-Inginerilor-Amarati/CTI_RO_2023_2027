#include <stdio.h>
#include <stdlib.h>
int vizite[8];
int a[8][8] = {{0,0,0,0,0,0,0,0},
{0,0,0,1,0,0,1,0},
{0,0,0,1,0,0,1,0},
{1,0,0,1,0,0,1,0},
{1,0,1,1,0,0,1,0},
{0,0,0,1,1,0,1,0},
{1,0,0,1,0,0,1,0},
{0,0,0,1,1,0,1,1}};

int main()
{
    int i,j,k;
    int n;
    scanf("dati numarul de noduri ale grafului ");
    scanf("%d",&n);  //citim numarul de noduri
    for(i=1;i<=n;i++)
		for(j=1;j<n;j++)  //parcurgem matricea de adiacenta a grafului
		{
			if(i!=j && a[i][j]==0) a[i][j]=1;  //daca intre nodul i si j nu avem muchie si nu suntem pe diag principala,o creeam
			else if (i!=j &&a[i][j]==1) a[i][j]=0;  //daca avem o muchie ,o stergem
		}
     for(i=1;i<=n;i++)
	 {
		for(j=1;j<n;j++)
		{
			printf("%d ",a[i][j]);  //afisam graful complementar
			printf("\n");
		}
	 }
    return 0;
}
