//2.Se da un arbore cu N noduri, prin tabloul cu indicatori spre parinte.Sa se scrie o functie care determina si afiseaza gradul arborelui(numarul de
//fii al nodului cu cel mai multi fii)

#include<stdio.h>
#include<stdlib.h>

int n, v[100];

int main() // nodul radacina are v[radacina] = 0, presupunem ca nodul radacina e nodul 1
{
    int i, j;
    scanf("%d", &n);
    for(i = 1; i <= n; i++){
        scanf("%d", &v[i]);
    }
    int nod = 0, gradmax = 0, grad = 0;
    for(i = 2; i <=n; i++)
    {
        nod = v[i];
        grad = 0;
        for(j = i; j <=n; j++)
        {
            if(v[j] == nod)
                grad++;
        }
        if(grad > gradmax)
            gradmax = grad;
    }
    printf("%d", gradmax);
    return 0;
}
