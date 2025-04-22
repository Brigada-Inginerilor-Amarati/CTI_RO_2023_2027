/*
6. Se citesc de la intrarea standard, 3 numere naturale S, n si e 

cu urmatoarele semnificatii: S este o suma de bani care trebuie platita 

folosind bancnote care au valori puterile lui e, 

de la e la 0, la e la n. 

Se se afiseze modalitatea de plata (câte bancnote de ce tip)

 folosind un numar minim de bancnote de tipurile precizate si
 
  sa se afiseze la final numarul total de bancnote folosite.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(void){
    int S = 0;
    int n = 0;
    int e = 0;
    scanf("%d %d %d", &S, &n, &e);
    int b = pow(e,n);
    int nr = 0;
    int total = 0;
    
    while(S > 0){
        nr = S/b;
        total += nr;
        S = S - nr*b;
        printf("%d * % d ", nr, b);
        b = b / e;
        if(S == 0){
            break;
        }
        printf("+");
    }
    printf("\n%d\n", total);
}