#include <stdio.h>
#include "stack.h"

int main(void)
{
    Stack_t st = init_Stack();

    st = push(st, 10);
    st = push(st, 20);
    Element_t el = peek(st);
    printf("Elementul din varf este %u\n", el);


    st = push(st, 30);

    el = peek(st);
    printf("Elementul din varf este %u\n", el);

    pop(st);

    el = peek(st);
    printf("Elementul din varf este %u\n", el);

    return 0;
}