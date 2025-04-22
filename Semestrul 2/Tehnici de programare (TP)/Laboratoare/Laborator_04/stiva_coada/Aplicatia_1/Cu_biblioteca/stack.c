#include "stack.h"

Stack_Code init_stack(stack *stiva, size_t cap)
{
    *stiva = (stack){0, 0, NULL};

    stiva -> data = (stack_data*) malloc(cap * sizeof(stack_data));

    if (stiva -> data == NULL)
    {
        stiva -> capacity = 0;
        return STACK_EMPTY;
    }

    stiva -> capacity = cap;
    return STACK_OK;
}

Stack_Code is_empty(stack *stiva)
{
    if(stiva -> stack_pointer == 0)
    {
        return STACK_EMPTY;
    }

    return STACK_OK;
}

Stack_Code is_full(stack *stiva)
{
    if(stiva -> stack_pointer >= stiva -> capacity)
    {
        return STACK_FULL;
    }

    return STACK_OK;
}

Stack_Code push(stack *stiva, stack_data element)
{
    if(is_full(stiva) == STACK_FULL)
    {
        stiva -> capacity += STACK_CHUNK;
        stiva -> data = (stack_data*) realloc (stiva -> data, stiva -> capacity * sizeof(stack_data));

        if(stiva -> data == NULL)
        {
            stiva -> capacity = 0;
            return STACK_FULL;
        }
        
    }

    stiva -> data[stiva -> stack_pointer ++] = element;
    return STACK_OK;
}

Stack_Code pop(stack *stiva)
{

}