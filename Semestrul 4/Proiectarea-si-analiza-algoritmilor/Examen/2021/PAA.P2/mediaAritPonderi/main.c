#include <stdio.h>
#include <stdlib.h>

float medie[22];
int a[55][55];
int main()
{
	int i,j,k,n,m;
	int p; //ponderea muchiei
    printf("dati numarul de noduri\n");
    scanf("%d",&n);
    printf("dati numarul de muchii\n");
    scanf("%d",&m);
		for(k=0;k<m;k++)
		{
			scanf("%d",&i);  //extremitatiile muchiei
			scanf("%d",&j);
			scanf("%d",&p);  //si ponderea sa
			  //asignam fiecarui element din  matrice ponderea
		}
	for(i=0;i<n;i++)
	{
		int suma=0;
		int noduri=0;
		for(j=0;j<n;j++)  //parcugrem matricea de adiacenta
		{
			suma+=p;
			noduri++;
		}
		if(noduri==0) return;
		medie[i]=suma/noduri;  //si facem minimul fiecarei linii
	}
	float min=9990;
	for(i=1;i<=n;i++)
		if(medie[i]< min) min=medie[i];  //gasim linia cu medie minima
	for(i=1;i<=n;i++)  //daca sunt mai multe ,mai parcugrem odata vecotorul de medii
		//if(medie[i] == min)  //si cand o gasim pe prima care minima
		//{
			printf("nodul %d are ponderea minima %f\n",i,medie[i]);  //o afisam
		//	break;  //si iesim
		//}


    return 0;
}
