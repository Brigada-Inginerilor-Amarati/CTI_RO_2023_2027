#include <stdio.h>
#include <stdlib.h>

int intCmp(const void *a, const void *b)
{
    // int a = *(int *)a;
    // int b = *(int*)b;

    const int pa = *(const int  *)a;
    const int pb = *(const int  *)b;


    return -(a - b); //descrescator 
}

double g(x)
{
    return (x * x) / 2;
}

//double (*f) double;
// un pointer la o functie care primeste double si returneaza double

void PrintValues(int a, int b, int pas, double (*f)(double))
{
    for (int i = a; i <= b; i += pas)
    {
        printf("%d %lf\n", i, f(i));
    }
}

//-Werror pt a arata ca erori warningurile 

int main(void)
{
    int v []= {3, 1, 4, 5, 6, 2, 1, 5};

    int n = sizeof(v) / sizeof(v[0]);
    //asta e corect doar in cadrul functiei unde e declarat vectorul

    qsort(v, n, sizeof(v[0]), intCmp);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
    }

    return 0;
}