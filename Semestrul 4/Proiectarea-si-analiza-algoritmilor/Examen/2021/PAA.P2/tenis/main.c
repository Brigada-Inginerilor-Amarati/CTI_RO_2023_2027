#include <stdio.h>
#include <stdlib.h>



int vizite[5];  //luam un vector de vizite pentru a marca jucatorii parcursi
int victorii[5];   //luam un vector de victorii,fiecare element e nr de victorii al jucatorului i

int main()
{
	int i,j,aux=0,n,max_i,k;
	printf("dati numarul de jucatori ");
	scanf("%d",&n);
	for(k=0;k<2*n;k++)  //5 jucatori ==> 10 meciuri
	{
		scanf("%d",&i);
		scanf("%d",&j);  //citim perechile de jucatori
		victorii[i]++;  //pt fiecar pereche ,dam o victorie jucatorului i
	}

	while(aux!=3)  //cat timp nu am gasit cei 3 jucatori cu cele mai multe victorii
	{
		int max=-9990;
		for(i=1;i<=n;i++)  //parcurgem jucatorii
			if(victorii[i] > max && vizite[i]==0)  //daca am vizitat jucatorul curent si el are un maxim de victorii
			{
				max=victorii[i];  //salvam maximul
		 	    max_i=i;  //si ii retinem pozitia
			}
			printf("jucatorul %d are %d victorii\n",max_i,max);  //afisam
			aux++;  //crestem numarul de jucatori cu victorii maxime pe care i-am gasit
			vizite[max_i]=1;  //marcam jucatorul cu victorii maxime ca fiind vizitat ca sa nu-l mai parcurgem odata
	}

    return 0;
}
