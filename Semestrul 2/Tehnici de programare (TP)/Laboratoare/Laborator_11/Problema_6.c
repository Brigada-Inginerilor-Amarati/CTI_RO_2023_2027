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

    int total_bancnote = 0;

    int suma = 0;
    int bancnota = pow(e, n);
    int k = 0;

    while(suma < S){
        if (bancnota <= S - suma)
        {
            suma = suma + bancnota;
            total_bancnote++;
            k++;  //nr pt tip de bancnota
        }
        else{
            if(k != 0){
                printf("%d bancnote de %d\n", k, bancnota);
            }
            k = 0;
            bancnota = bancnota / e;
        }
    }
    printf("%d bancnote de %d\n", k, bancnota);
    printf("Nr de bancnote : %d\n", total_bancnote);
    return 0;
}