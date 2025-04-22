/*
 * 1 [Prelucrari de matrici]

Pentru cerintele de mai jos se va considerare o matrice "oarecare", cu m linii (<=100) si n coloane (<=100), elementele fiind numere intregi. Fiecare cerinta se va implementa sub forma unei functii distincte.

Nu se accepta utilizarea de variabile globale, iar "constantele globale" vor fi definite prin #define. Datele vr fi fie generate algoritmic (folosind rand/srand si conexe), fie vor fi citite prin redirectarea intrarii standard.

Ideile de cerinte sunt inspirate din pbinfo.ro , pe care il puteti folosi pentru a exersa suplimentar.

- să se determine, pentru fiecare linie, cea mai mică valoare care se poate obține adunând elementele de pe linie, cu excepția unuia;

- să se determine câte dintre elementele situate pe linii cu indici pari sunt prime.

- să se permute coloanele matricei circular spre stânga cu o poziție.

- sa se interschimbe valoarea minimă din ultima coloană a tabloului cu valoarea maxima din prima coloană a tabloului, apoi sa se afiseze ecran tabloul modificat;

- să se determine câte linii ale matricei au toate elementele egale.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generare_matrice(int matrice[100][100], int nr_randuri, int nr_coloane)
{
    for(int i = 0; i < nr_randuri; i++)
    {
        for(int j = 0; j < nr_coloane; j++)
        {
            matrice[i][j] = rand() % 100;
        }
    }
}

void afisare_matrice(int matrice[100][100], int nr_randuri, int nr_coloane)
{
    for(int i = 0; i < nr_randuri; i++)
    {
        for(int j = 0; j < nr_coloane; j++)
        {
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }
}

int suma_minima(int matrice[][100], int nr_randuri, int nr_coloane)
{
    int suma = 0;
    int maxim = matrice[nr_randuri][0];
    for(int i = 0; i < nr_coloane; i++)
    {
        suma = suma + matrice[nr_randuri][i];

        if(matrice[nr_randuri][i] > maxim)
        {
            maxim = matrice[nr_randuri][i];
        }
    }

    suma = suma - maxim;
    return suma;
}

int este_prim(int n)
{
    for(int i = 2; i <= n / 2; i++)
    {
        if(n % i ==0)
        {
            return 0;
        }
    }
    return 1;
}

int nr_prime(int matrice[][100], int nr_randuri, int nr_coloane)
{
    int contor = 0;
    for(int i = 0; i < nr_coloane; i++)
    {
        if(este_prim(matrice[nr_randuri][i]))
        {
            contor++;
        }
    }

    return contor;
}

void permutare(int mat[][100], int nr_randuri, int nr_coloane, int linie_permutata[][100])
{
    for(int j = 1; j < nr_coloane; j++)
    {
        linie_permutata[nr_randuri][j-1] = mat[nr_randuri][j];
    }
}

void interschimba(int matrice[][100], int nr_randuri, int nr_coloane, int mat_noua[][100])
{
  int max = matrice[0][0];
  int min = matrice[0][nr_coloane-1];
  int slot=0;

  for(int i = 1; i < nr_randuri; i++)
    {
      if(matrice[i][0] > max)
          max = matrice[i][0];
      if(matrice[i][nr_coloane - 1] < min)
      {
          min = matrice[i][nr_coloane - 1];

          slot = i;

    }

    }

  //matrice noua
  for(int i=0; i<nr_randuri; i++)
    {
      for(int j=0; j<nr_coloane - 1; j++)
	        mat_noua[i][j] = matrice[i][j];
    }
  for(int i=0; i<nr_randuri; i++)
    {
      if(i != slot)
	    mat_noua[i][nr_coloane-1] = matrice[i][nr_coloane-1];
      else
	    mat_noua[i][nr_coloane-1] = max;
    }
}


int egale(int mat[][100], int linii, int coloane)
{
  int ct=0;
  for(int i=0; i<linii; i++)
    {
      for(int j=1; j<coloane; j++)
	{
	  if(mat[i][j] != mat[i][0])
	    {
	      ct--;
	      break;
	    }
	}
      ct++;
    }
  return ct;
}

int main(void)
{
    srand(time(NULL));

    int nr_randuri = rand() % 10 + 1;
    int nr_coloane = rand() % 10 + 1;

    int matrice[100][100];

    generare_matrice(matrice, nr_randuri, nr_coloane);
    afisare_matrice(matrice, nr_randuri, nr_coloane);

    //suma minima

    for(int i = 0; i < nr_randuri; i++)
    {
        printf("Linia %d : suma minima = %d \n", i + 1, suma_minima(matrice,i, nr_coloane));
    }
    printf("\n");

    return 0;
}
