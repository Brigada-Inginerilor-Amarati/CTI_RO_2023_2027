#include <stdio.h>
#include "coada.h"

int compare(void *el1, void *el2)
{
    el e1 = *((el *)el1);
    el e2 = *((el *)el2);
    return e1 > e2;
}

int main(void)
{
    PQ_T que = create(6);

    if (insert(que, 4, compare) != OK) {
        printf("err");
    }
    insert(que, 3, compare);
    insert(que, 2, compare);
    insert(que, 5, compare);
    if (insert(que, 10, compare) != OK) {
        printf("ERR\n");
    }
    insert(que, 7, compare);
    el variable = 0;
    while (deque(que, &variable) != -1) {
        printf("value from que : %d\n", variable);
    }

    destruct(que);

    return 0;
}