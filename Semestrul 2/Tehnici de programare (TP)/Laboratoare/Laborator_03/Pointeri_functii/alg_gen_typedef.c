#include <stdio.h>

typedef int(*Conditie)(int);

int pozitiv(int e)
{
    return e >= 0;
}

int par(int e)
{
    return e % 2 == 0;
}

int testare(int *v, int n, Conditie cond)
{
    int i;

    for(i = 0; i < n; i++)
    {
        if(!cond(v[i])) 
        {
            return 0;
        }
    }
        
    return 1;
    
}

int main(void)
{
    int v[5] = {4,8,1,2,0};

    printf("toate elementele sunt pozitive: %d \n", testare(v, 5, pozitiv));

    printf("toate elementele sunt pozitive: %d \n", testare(v, 5, par));
    return 0;
}