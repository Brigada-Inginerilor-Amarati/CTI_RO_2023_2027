#include <stdio.h>
#include <stdlib.h>


int t[8];
int d[8];
int vizite[8];
int drum[111];
int a[55][55];
int main()
{
	int i,j,min_i,min_j,aux1,aux2,aux3,n,m;
    scanf("%d",&n);
    scanf("%d",&m);
    for(i=0;i<n;i++)
	{
		scanf("%d %d %d ",aux1,aux2,aux3);  //inter1,inter2,lungime strada
	}
    vizite[aux1]=1;
    for(i=0;i<7;i++)
	{
		d[i]=a[aux1][i]; //distanta dintre julieta si toate intersectiile
	}

    for(j=0;j<=6;j++)
	{
		int min=9990;
		for(i=0;i<=7;i++)
		{
            if(vizite[i]==0 && d[i]<min && d[i]!=0)
			{
				min=d[i];
				min_i=i;
			}
		}
		vizite[min_i]=1;
		for(i=1;i<=7;i++)
		{
			if(d[i] > a[min_i][i] + d[min_i])				//facem Dikjstra pentru drumurile Julietei
			{
				d[i] > a[min_i][i] + d[min_i];
				t[i]=min;
			}
		}
	}
	i=aux1; //julieta
	int contor=0;
	while(1)
	{
		if(t[i]==t[aux2])
		{
			drum[contor++]=t[i];  //Daca am ajung la nodul unde este Romeo adaugam nodul la drum si iesim
			break;
		}
		drum[contor++]=t[i];  //ca sa avem in ordine drumul de la romeo la julieta
		t[i]=t[t[i]];

	}
    int suma=0;
    for(i=0;i<contor-1;i++)
	{
        suma+a[i][i+1];  //calculam lungimea drumului dintre romeo si julieta
	}
	int suma2=0,suma3=0;
	printf("Julieta\n");
	for(i=0;i<contor;i++)
	{
		aux3=i; //memoram unde a ramas julieta
		if(suma > suma/2)
		{
			printf("nodul de intalnire este %d",t[i]);
			break;
		}
		suma2+=d[i];
	}
	printf("%d",t[i]);
    //Romeo
    printf("Romeo");
    while(aux3<contor)  //aux 3 retine ultima poztie a julietei,cat timp nu am ajuns la ea
	{
        printf("%d",t[aux3]);  //adunam distante la drumul lui Romeo
        suma3+=d[aux3];
        aux3++;

	}

	printf("Romeo merge %d",suma3);
	printf("Julieta merge %d",suma2);
    return 0;
}
