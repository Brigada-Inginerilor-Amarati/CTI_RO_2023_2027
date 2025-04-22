#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

stack init_stack(size_t cap) {
    stack st = {0, cap, NULL};
    st.data = (stack_data *)malloc(cap * sizeof(stack_data));
    if (st.data == NULL) {
        st.capacity = 0;
        return st;
    }
    return st;
}

stack push(stack *st, stack_data data) {
    if (st->top >= st->capacity)
        return *st;
    st->data[st->top++] = data;
    return *st;
}

stack_data pop(stack *st) {
    if (st->top == 0)
        return 0;
    st->top--;
    return st->data[st->top];
}

stack_data peek(stack *st) {
    if (st->top == 0)
        return 0;
    return st->data[st->top - 1];
}

void free_stack(stack *st) {
    free(st->data);
}

int check_validity(char *str) {
    size_t capacity = strlen(str);
    stack st = init_stack(capacity);
    if (st.data == NULL)
        return -1;
    st = push(&st, str[0]);
    for (size_t i = 1; i < capacity; i++) {
        switch (str[i]) {
            case ')':
                if (peek(&st) == '(')
                    pop(&st);
                else
                    st = push(&st, str[i]);
                break;
            case ']':
                if (peek(&st) == '[')
                    pop(&st);
                else
                    st = push(&st, str[i]);
                break;
            case '}':
                if (peek(&st) == '{')
                    pop(&st);
                else
                    st = push(&st, str[i]);
                break;
            default:
                st = push(&st, str[i]);
                break;
        }
    }
    free_stack(&st);
    return st.top == 0;
}
