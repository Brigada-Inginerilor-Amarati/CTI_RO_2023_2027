/*
Se dau trei numere naturale n a b, 1 ≤ a < b < n. 

Să se determine o modalitate de a-l scrie pe n ca sumă de 

termeni egali cu a sau b în care numărul de termeni egali cu a este maxim. 

La intrare se vor citi n a si b, in aceasta ordine, iar la iesire se va scrie 

valoarea numarului de aparitii ale lui a si ale lui b, in aceasta ordine, separate prin minim un spatiu.
*/

#include <stdio.h>

int main(void){
    int n = 0;
    int a = 0;
    int b = 0;

    scanf("%d",&n);
    scanf("%d",&a);
    scanf("%d",&b);

    int contor_a = 0;
    int contor_b = 0;

    contor_a = n / a;

    while(1){

        if((n - contor_a * a) % b == 0){
            contor_b = (n - contor_a * a) / b;
            break;
        }

        contor_a--;
    }

    if(contor_a < 0){
        printf("Nu exista \n");
    }

    printf("%d %d\n", contor_a, contor_b);
    return 0;
}