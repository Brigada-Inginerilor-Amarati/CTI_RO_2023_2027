/*
1. Se dă o colectie cu n numere întregi (varainta: numere naturale).

Determinați cel mai mare număr care poate fi scris ca produs de două elemente ale șirului.

La intrare se va citi un numar n si apoi n numere intregi/naturale separate prin minim un spatiu,

iar la iesire se va scrie un singur numar care este rezultatul solicitat.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void){

    int n;
    int max_neg_low = 0;
    int max_neg_up = 0;
    int max_pos_low = 0; 
    int max_pos_up = 0;

    scanf("%d", &n);


    for (int i = 0; i < n; i++)
    {
        int x = 0;
        scanf("%d", &x);

        if(x > 0){

            if(x > max_pos_up){
                max_pos_low = max_pos_up;
                max_pos_up = x;
            }
            else if(x > max_pos_low){
                max_pos_low = x;
            }
            
        }
        else{

            if(x < max_neg_up){
                max_neg_low = max_neg_up;
                max_neg_up = x;
            }
            else if(x < max_neg_low){
                max_neg_low = x;
            }
        }
    }
    
    int max_neg = max_neg_low * max_neg_up;

    int max_pos = max_pos_low * max_pos_up;

    if(max_neg > max_pos){
        printf("%d\n", max_neg);
    }
    else{
        printf("%d\n", max_pos);
    }

    return 0;
}