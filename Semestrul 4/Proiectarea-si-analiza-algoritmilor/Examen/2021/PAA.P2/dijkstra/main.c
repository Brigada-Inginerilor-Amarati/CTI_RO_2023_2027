#include <stdio.h>
#include <stdlib.h>
int vizite[8];  //luam un vector de vizite
int d[8];  //vectorul D din algoritmul lui Dijkstra
int t[8];   //vectorul T din algoritmul lui Dijkstra
int a[100][100] = { { 999, 9, 1, 3, 999, 999, 9, 999 },
					{ 999, 999, 999, 999, 999, 999, 999, 999 },
					{ 999, 999, 999, 999, 2, 5, 999, 999 },
					{ 999, 999, 999, 999, 999, 999, 5, 999 },
					{ 999, 999, 999, 999, 999, 1, 999, 999 },
					{ 999, 999, 999, 999, 999, 999, 1, 999 },
					{ 999, 999, 999, 999, 999, 999, 999, 999 },
					{ 999, 999, 999, 999, 1, 999, 4, 2 } };

					//cand avem 999 inseamna ca nu avem drum (e infinit)
int main()
{
    int i,j,k,min_i;
    vizite[0]=1;  //pornim de la primul nod,il marcam ca vizitat
    for(i=0;i<=7;i++)  //initializam toate intrarile vecotorului D cu primul la nod la primul pas
	{
		d[i]=a[0][i];
	}

		int min=9990;
		for(j=0;j<=6;j++)
		{
			for(i=0;i<=7;i++)  //parcurgem graful
			{
                if(d[i] < min && d[i]!=999 && vizite[i]==0)  //daca avem pondere minima si drum care sa nu fie infinit si nodul curent nu e vizitat
				{
					min=d[i];  //atunci salvam noul minim
					min_i=i;   //si ii retinem pozitia
				}
			}
			vizite[min_i]=1;  //marcam nodul curent ca vizitat,ca data viitoare sa pornim de unde am ramas
			for(i=1;i<=7;i++)
			{
                if(d[i] > a[min_i][i] + d[min_i])  //verificam daca ponderea initiala e mai mare decat ponderea arcului dintre nodul de start si cel curent + ponderea de la nodul curent la nodul destinatie
				{
					d[i] =a[min_i][i] + d[min_i];  //daca da,inseamna ca am gasit un traseu mai mic ca distanta
					t[i]=min;  //si modificam intrarea in vecotorul T cu nodul prin care am gasit un drum minim
				}
			}
		}
			for (i = 0; i <=7 ; i++)
				printf("%d \t\t %d\n", i, d[i]);  //afisare a drumului minim si costurilor intre muchiile sale
    return 0;
}
