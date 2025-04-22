/*
f(x) = sin(x) + sin(2 * x) + x si o valoare y

f - strict crescatoare pe [0, 1)

x = ? x e [0, 1) a.i f(x) = y (aproximat 8 zecimale)
*/

#include <stdio.h>
#include <math.h>

double functie(double x){
    return sin(x) + sin(2 * x) + x;
}

//recursivitate

double bisectie(double y, double a, double b, double (*f)(double), double tol){
    double mijloc = (a + b) / 2;

    if((b - a) / 2 < tol){
        return mijloc;
    }

    if (f(mijloc) < y){
        return bisectie(y, mijloc, b, f, tol); // cautam mai la dreapta
    }
    else{
        return bisectie(y, a, mijloc, f, tol); //cautam mai la stanga
    }
    
}

double iterativ(double y, double a, double b, double (*f)(double), double tol){
    while((b - a) / 2 > tol){
        double mijloc = (a + b) / 2;

        if(f(mijloc) < y){
            a = mijloc;
        }
        else{
            b = mijloc;
        }
    }

    return (a + b) / 2;
}

int main(void){
    double y;
    scanf("%lf", &y);

    printf("%.8lf" , iterativ(y, 0, 1, functie, pow(10, -8)));
}