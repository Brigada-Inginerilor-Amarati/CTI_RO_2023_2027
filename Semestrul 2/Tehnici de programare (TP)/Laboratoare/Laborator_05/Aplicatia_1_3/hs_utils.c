#include "hs_utils.h"

int ePalindrom(unsigned num)
{
    unsigned reversed = 0;
    unsigned original = num;

    while(num != 0)
    {
        reversed = reversed * 10 + num % 10;

        num/= 10; 
    }

    return original == reversed;
}

unsigned getFibboTerm(unsigned n)
{
    if(n <= 1)
    {
        return n;
    }

    unsigned prev = 0;
    unsigned curr = 1;

    for(unsigned i = 2; i <= n; i++)
    {
        unsigned next = prev + curr;
        prev = curr;
        curr = next;
    }

    return curr;
}