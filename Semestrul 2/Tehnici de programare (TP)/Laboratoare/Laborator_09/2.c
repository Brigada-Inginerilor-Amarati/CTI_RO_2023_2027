/*
Găsiţi, cu o aproximaţie dată (de exemplu 10-6), o rădăcină a unei funcţii f

 continuă pe un interval [a, b] şi care schimbă semnul pe acel interval (adică o valoare 
 
 x pentru care f(x) = 0).


Rezolvaţi problema pentru o funcţie dată (de exemplu f(x) = x2 - 3) pe care o definiţi în program,

 şi alegeţi valori corespunzătoare pentru a şi b (de exemplu 1 şi 3).


Indicaţii Deoarece f(a) ≤ 0 (f(1) = 1 * 1 - 3 = -2) şi f(b) ≥ 0 (f(3) = 3*3 - 3 = 6) iar funcţia e continuă pe [a, b], ea va avea o rădăcină în acest interval. Problema se rezolvă înjumătăţind la fiecare pas intervalul de căutare pe care funcţia schimbă semnul, până când acesta devine mai mic decât precizia dată. Atunci orice punct din interval e o soluţie cu precizia cerută.
Se calculează valoarea funcţiei în mijlocul intervalului. Dacă valoarea funcţiei e ≥ 0, funcţia schimbă semnul pe jumătatea din stânga a intervalului. Altfel (dacă valoarea funcţiei la mijlocul intervalului e < 0), funcţia schimbă semnul pe jumătatea din dreapta. (în exemplul dat, f(2) = 2*2 - 3, şi cum f(2) ≥ 0, continuăm cu intervalul [1,2]). Ajungem astfel la aceeaşi problemă, dar cu intervalul redus la jumătate. Continuând să înjumătăţim lungimea intervalului ajungem la cazul de bază, când putem returna orice valoare din interval (de exemplu mijlocul).
Se poate eventual testa suplimentar dacă în mijlocul intervalului, funcţia are valoarea zero, şi returna direct rădăcina în acest caz. 

*/

#include <stdio.h>
#include <stdlib.h>

double functie(double x){
    return x * x - 3;
}

double radacina(double (*f) (double), double a, double b, double tol){
    if(f(a) * f(b) >= 0){
        perror("nu i bun \n");
        exit(EXIT_FAILURE);
    }

    double c;

    if((b - a) / 2 > tol){
        c = (a + b) / 2;

        if(f(c) == 0){
            return c;
        }

        if(f(a) * f(c) < 0){
            b = c;
        }
        else{
            a = c;
        }

        return radacina(f, a, b, tol);
    }

    return (a + b) / 2;
}

int main(int argc, char ** argv){
    if(argc != 3){
        perror("bam\n");
        return -1;
    }

    double tol = 0.000001;
    printf("%lf \n", radacina(functie, atoi(argv[1]), atoi(argv[2]), tol)); 
    return 0;   
}