#include <stdio.h>
#include <stdlib.h>
int vizite[7];   //luam un vector de vizite pentru a marca nodurile pe care le vizitam
int a[100][100] = { { 0, 0, 0, 0, 0, 0, 0, 0 },//a
{ 0, 0, 1, 2, 0, 10, 0, 0 },//b
{ 0, 1, 0, 0, 1, 0, 0, 0 },//c
{ 0, 2, 0, 0, 0, 4, 0, 3 },//d
{ 0, 0, 1, 0, 0, 1, 0, 0 },//e
{ 0, 10, 0, 4, 1, 0, 1, 0 },//f
{ 0, 0, 0, 0, 0, 1, 0, 1 },//g
{ 0, 0, 0, 3, 0, 0, 1, 0 } };//h
int main()
{
	int suma=0;
	int i,j,k,n,aux_j,aux_i;
    printf("dati numarul de noduri ale grafului \n");
    scanf("%d",&n);
    vizite[1]=1;
    for(k=0;k<6;k++)  //repetam acest procedeu pana cand U=N
	{
		int min=9990;
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=n;j++)  //parcurgem matricea de adiacenta
			{
                if(vizite[i]==1 && vizite[j]==0)  //daca nu am terminat de vizitat linia curenta
                {
                    if(min > a[i][j] && a[i][j]!=0)  //si gasim o pondere minima nenula
					{
						min=a[i][j];  //atunci setam minimul
						aux_i=i;  //si ii retinem pozitiile ,ca sa le marcam ca vizitate,astfel la urmatorul pas,pornim de unde am ramas,ca sa nu mai parcurgem odata ce a fost deja vizitat
						aux_j=j;
					}
				}
			}
		}
		vizite[aux_j]=1;  //aici marcam vizita pana in momentul curent (adaugam elemntul in U)
		suma+=min;  //adaugam ponderea minima la suma care reprezinta  drumul minim
		printf("%d",aux_i);
		printf("-");
		printf("%d",aux_j);   //la liniile astea 3 afisam muchiile care alcatuiesc arborele de acoperire minim
		printf("\n");
	}
	printf("Drumul minim rezultat din arborele de acoperire minim este %d",suma);  //afisam costul arborelui de acoperire

    return 0;
}
