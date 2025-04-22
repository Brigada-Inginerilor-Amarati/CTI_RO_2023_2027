/*
 * 2 [Pbinfo1749]

Considerăm o matrice pătratică cu N linii și N coloane. În această matrice sunt definite 4 zone:

    zona 1, formată din elementele situate strict deasupra diagonalei principale și strict deasupra diagonalei secundare;
    zona 2, formată din elementele situate strict deasupra diagonalei principale și strict sub diagonala secundară;
    zona 3, formată din elementele situate strict sub diagonala principală și strict sub diagonala secundară;
    zona 4, formată din elementele situate strict sub diagonala principală și strict deasupra diagonalei secundare;

Implementati o functie care primeste o matrice pătratică și un număr natural Z, reprezentând o zonă din matrice. Să se determine suma elementelor din zona Z.
 */
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

int aduna_elemente_zona(int matrice[][NR_RND], int nr_randuri, int Z)
{
    int S = 0;
    for(int i = 0; i < nr_randuri; i++)
    {
        for(int j =  0; j < nr_randuri; j++)
        {
            switch (Z)
            {
            case 1:
                if(i < j && i + j < nr_randuri + 1)
                {
                    S = S + matrice[i][j];
                }
                break;

            case 2:
                if(i < j && i + j > nr_randuri + 1)
                {
                    S = S + matrice[i][j];
                }
                break;
            
            case 3:
            if(i > j && i + j > nr_randuri + 1)
                {
                    S = S + matrice[i][j];
                }
                break;
            
            case 4:
            if(i > j && i + j < nr_randuri + 1)
                {
                    S = S + matrice[i][j];
                }
                break;
            default:
                break;
            }
        }
    }

    return S;
}



int main(void)
{
    srand(time(NULL));

    int matrice[NR_RND][NR_COL], nr_randuri, nr_coloane;

    nr_randuri = rand() % 10 + 1; //100
    nr_coloane = nr_randuri;

    int Z = 0;
    Z = rand() % 4 + 1;
    printf("%d \n", Z);

    citeste_matrice(matrice, nr_randuri, nr_coloane);
    afiseaza_matrice(matrice, nr_randuri, nr_coloane);
    printf("Suma elementelor din zona %d este : %d \n",Z, aduna_elemente_zona(matrice, nr_randuri, Z));



    return 0;
}
