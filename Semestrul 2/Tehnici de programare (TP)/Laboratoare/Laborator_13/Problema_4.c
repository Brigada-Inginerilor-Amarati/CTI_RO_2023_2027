/*
https://www.pbinfo.ro/probleme/342/soarece

Se dă o tablă dreptunghiulară formată din n linii și m coloane,

definind n*m zone, unele dintre ele fiind libere, altele conținând obstacole. 

În zona aflată la poziția is, js se află un șoarece care se poate deplasa pe tablă 

trecând din zona curentă în zona învecinată cu aceasta pe linie sau pe coloană. 

Scopul sau este să ajungă la o bucată de brânză aflată în zona de la poziția ib, jb, 

fără a părăsi tabla, fără a trece prin zone care conțin obstacole și fără a trece de 

două ori prin aceeași zonă.

Determinați câte modalități prin care șoarecele poate ajunge de la poziția inițială 

la cea a bucății de brânză există.

DATE DE INTRARE

Fişierul de intrare soarece.in conţine pe prima linie numerele n m, 

separate printr-un spațiu. Următoarele n linii conțin câte m valori 0 sau 1, 

separate prin exact un spațiu, care descriu tabla – valoarea 0 reprezintă o zonă liberă, 

valoarea 1 reprezintă o zonă ocupată cu un obstacol. Pe linia n+2 se află 4 numere separate 

prin exact un spațiu, reprezentând is js ib jb.

DATE DE IESIRE

Fişierul de ieşire soarece.out va conţine pe prima linie numărul S, 

reprezentând numărul de modalități prin care șoarecele poate ajunge de 

la poziția inițială la cea a bucății de brânză.
*/

#include <stdio.h>
#include <stdlib.h>

int n = 6, m = 7;

int a[6][7] ={
{0, 0, 0, 0, 0, 0, 0},
{0, 1, 1, 1, 1, 0, 0},
{0, 0, 0, 0, 1, 1, 0},
{0, 1, 1, 0, 1, 0, 0},
{0, 1, 1, 0, 1, 0, 1},
{0, 0, 0, 0, 0, 0, 0}
};

int si = 4, sj = 1;
int bi = 2, bj = 6;

int pas = 13;


void print_matrice(int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%2d ", a[i][j]);
        }
        printf("\n");
    }

    printf("-----------\n");
}

int nr_drumuri = 0;

void fill(int i, int j){
    a[i][j]=pas;

    pas++;

    if (i==bi && j==bj){
        printf("AM GASIT BRANZA LA (%d, %d)\n", i, j);
        nr_drumuri++;
        print_matrice(n, m);
    }

    if (i>0 && a[i-1][j]==0) fill(i-1, j);   //N

    if (i<n-1 && a[i+1][j]==0) fill(i+1, j);   //S

    if (j<m-1 && a[i][j+1]==0) fill(i, j+1);   //E

    if (j>0 && a[i][j-1]==0) fill(i, j-1);   //W

    a[i][j]=0;  //sterg urma, marcand celula la valoarea ei originala --> 

    pas--;      //permite urmatirea vizuala a tuturor traseelor 
                //(la fiecare intersectie genereaza toate posibilitatile a "o lua" pe ramifcatii)
}


int main(void){
    print_matrice(n,m);

    fill(si, sj);

    printf("%d \n", nr_drumuri);

    return 0;
}
