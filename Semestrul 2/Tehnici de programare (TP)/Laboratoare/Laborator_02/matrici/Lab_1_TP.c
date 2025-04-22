#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NR_RND 100
#define NR_COL 100

void citeste_matrice(int matrice[][NR_COL], int nr_randuri, int nr_coloane)
{
    for(int i = 0; i < nr_randuri; i++)
    {
        for(int j = 0; j < nr_coloane; j++)
        {
            matrice[i][j] = rand() % 100;
        }
    }
}
void citeste_matrice_tastatura(int matrice[][NR_COL], int nr_randuri, int nr_coloane)
{
        for(int i = 0; i < nr_randuri; i++)
    {
        for(int j = 0; j < nr_coloane; j++)
        {
            int x;
            scanf("%d", &x);
            matrice[i][j] = x;

        }
    }
}

void afiseaza_matrice(int matrice[][NR_COL], int nr_randuri, int nr_coloane)
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

int suma_minima_linie(int matrice[][NR_COL], int linie, int nr_coloane)
{
    int suma = 0;
    int maxim = matrice[linie][0];
    
    for(int i = 0; i < nr_coloane; i++)
    {
        suma = suma + matrice[linie][i];
        
        if(matrice[linie][i] > maxim)
        {
            maxim = matrice[linie][i];
        }
    }
    
    suma = suma - maxim;
    return suma;
}

int este_prim(int n)
{
    for(int i = 2; i <= n/2; i++)
    {
        if(n % i == 0)
        {
            return 0;
        }
    }
    
    return 1;
}

int gaseste_nr_prime_linie(int matrice[][NR_COL], int linie, int nr_coloane)
{
    int contor = 0;
    for(int i = 0; i < nr_coloane; i++)
    {
        if(este_prim(matrice[linie][i]))
        {
            contor++;
        }
    }
    
    return contor;
}

void permuta_circular_stanga(int matrice[][NR_COL], int linie, int nr_coloane, int linie_permutata[][NR_COL])
{
    int i = 0;
    for(i = 1; i < nr_coloane; i++)
    {
        linie_permutata[linie][i - 1] = matrice[linie][i];
    }
    linie_permutata[linie][nr_coloane - 1] = matrice[linie][0];
}

// void permutare_2(int matrice[][NR_COL], int nr_randuri, int nr_coloane, int linie_permutata[][NR_COL])
// {
//     int aux[nr_randuri];
//     for(int i = 0; i < nr_randuri; i ++)
//     {
//         aux[i] = matrice[i][0];
//     }
//     
//     for(int i = 0; i < nr_randuri; i++)
//     {
//         for(int j = 0; j < nr_coloane; j++)
//         {
//             matrice[i][j-1] = matrice[i][j];
//         }
//     }
//     
//     for(int i = 0; i < nr_randuri; i++)
//     {linie_permutata[i][nr_coloane - 1] = matrice[i][0];
//         matrice[i][nr_coloane - 1] = aux[i];
//     }
// }

int gaseste_maxim(int matrice[][NR_COL], int nr_randuri, int nr_coloane)
{
    int maxim = matrice[0][0];
    
    for(int i = 0; i < nr_randuri; i++)
    {
        if(matrice[i][0] > maxim)
        {
            maxim = matrice[i][0];
        }
    }
    
    return maxim;
}

int gaseste_minim(int matrice[][NR_COL], int nr_randuri, int nr_coloane)
{
    int minim = matrice[0][nr_coloane - 1];
    
    for(int i = 0; i < nr_randuri; i++)
    {
        if(matrice[i][nr_coloane - 1] < minim)
        {
            minim = matrice[i][nr_coloane - 1];
        }
    }
    
    return minim;
}

void interschimba_max_min(int matrice[][NR_COL], int nr_randuri, int nr_coloane)
{
    int minim = gaseste_minim(matrice, nr_randuri, nr_coloane);
    int maxim = gaseste_maxim(matrice, nr_randuri, nr_coloane);
    
    for(int i = 0; i < nr_randuri; i++)
    {
        if(matrice[i][0] == maxim)
        {
            matrice[i][0] = minim;
        }
        
        if(matrice[i][nr_coloane - 1] == minim)
        {
            matrice[i][nr_coloane - 1] = maxim;
        }
    }
}

int egale(int matrice[][100], int nr_randuri, int nr_coloane)
{
  int ct=0;
  for(int i = 0; i<nr_randuri; i++)
    {
      for(int j = 1; j< nr_coloane; j++)
	{
	  if(matrice[i][j] != matrice[i][0])
	    {
	      ct--;
	      break;
	    }
	}
      ct++;
    }
  return ct;
}

int egale2(int matrice[][NR_COL], int linie, int nr_coloane)
{
    int ct = nr_coloane;
    for(int i = 0; i < nr_coloane; i++)
    {
        if(matrice[linie][i] != matrice[linie][0])
        {
            return 0;
        }

    }
    return ct;
}

int main(void)
{
    srand(time(NULL));
    
    int nr_randuri, nr_coloane;
    
    nr_randuri = 3;//rand() % 10 + 1; //100
    nr_coloane = 3;//rand() % 10 + 1; //100
    
    int matrice[NR_RND][NR_COL];
    
    citeste_matrice_tastatura(matrice, nr_randuri, nr_coloane);
    afiseaza_matrice(matrice, nr_randuri, nr_coloane);
    
    //suma minima pe linii
    for(int i = 0; i < nr_randuri; i++)
    {
        printf("Suma minima pe linia %d este %d \n", i, suma_minima_linie(matrice, i, nr_coloane));
    }
    
    printf("\n");
    
    //elemente prime pe linii cu indici pari sunt prime
    for(int i = 0; i < nr_randuri; i += 2)
    {
        printf("Pe linia %d sunt %d nr prime \n", i, gaseste_nr_prime_linie(matrice, i, nr_coloane));
    }
    
    printf("\n");
    
    //permutare coloane circular spre stanga cu o pozitie
    int linie_permutata[NR_RND][NR_COL];
    
   for(int i = 0; i < nr_randuri; i++)
     {
        permuta_circular_stanga(matrice, i, nr_coloane, linie_permutata);
   } 
    
    afiseaza_matrice(linie_permutata, nr_randuri, nr_coloane);
    
    
    printf("\n");
    
    //interschimbare val minima din ultima coloana cu valoarea maxima din prima coloana
    
    interschimba_max_min(matrice, nr_randuri, nr_coloane);
    
    afiseaza_matrice(matrice, nr_randuri, nr_coloane);
    
    printf("\n");
    
    //cate linii ale matricei au elemente egale

    int nr = 0;
    int contor = 0;
    for(int i = 0; i < nr_randuri; i++)
    {
        contor = egale2(matrice, i, nr_coloane);
        if(contor){
            printf("Linia %d are toate elementele egale.\n", i + 1);
            nr++;
        }
    }

    printf("Exista %d linii cu elementele egale.\n", nr);
    
    return 0;
}
