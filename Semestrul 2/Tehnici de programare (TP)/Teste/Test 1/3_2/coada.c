#include <stdio.h>
#include <stdlib.h>
#include "coada.h"

typedef struct
{
    el value;
    size_t vechime;
} El_t;

struct coada
{
    El_t *data;
    size_t max_capacity;
    size_t position;
    size_t head;
    size_t *istoric;
};

PQ_T create(unsigned max_capacity)
{
    PQ_T new_que = malloc(sizeof(struct coada));
    new_que->data = calloc(max_capacity, sizeof(El_t)); //folosim calloc pentru a aloca memorie si a o initializa cu 0
    new_que->max_capacity = max_capacity;
    new_que->position = 0;
    new_que->head = 0;
    new_que->istoric = calloc(max_capacity, sizeof(size_t));
    return new_que;
}

void shift_data_to_right(PQ_T que, size_t first_position, size_t last_position)
{
    for (; last_position > first_position; last_position--)
    {
        que->data[last_position] = que->data[last_position - 1];
        que->istoric[que->data[last_position - 1].vechime]++;
    }
}

void shift_data_to_left(PQ_T que, size_t first_position, size_t last_position)
{
    for (; first_position < last_position - 1; first_position++)
    {
        que->data[first_position] = que->data[first_position + 1];
        que->istoric[que->data[first_position].vechime]--;
    }
}

void show_ordered_data(PQ_T que)
{
    printf("Values : \n");
    for (size_t i = 0; i < que->position; i++)
    {
        printf("%d ", que->data[i].value);
    }
    printf("\n History : \n");
    for (size_t i = 0; i < que->position; i++)
    {
        printf("%ld ", que->istoric[i]);
    }
    printf("\n");
}

COD insert(PQ_T que, el value, int (*compare)(void *el1, void *el2))
{
    if (que->position == que->max_capacity)
    {
        return Q_FULL;
    }
    El_t element = {.value = value, .vechime = que->position};

    size_t i = 0;

    for (; i < que->position; i++)
    {
        if (compare(&element.value, &que->data[i].value) == 0)
        {
            shift_data_to_right(que, i, que->position);
            break;
        }
    }

    que->data[i] = element;
    que->istoric[que->position] = i;
    que->position++;
    show_ordered_data(que);

    return OK;
}

void reset_history(PQ_T que)
{
    for (size_t i = 0; i < que->position; i++)
    {
        que->data[i].vechime--;
        que->istoric[i] = que->istoric[i + 1];
    }
}

int deque(PQ_T que, el *address_to_receive_data)
{
    if (que->position == 0)
    {
        return -1;
    }
    else
    {
        if (address_to_receive_data != NULL)
        {
            *address_to_receive_data = que->data[que->istoric[0]].value;
        }
        shift_data_to_left(que, que->istoric[0], que->position);
        que->position--;
        reset_history(que);
        show_ordered_data(que);
        return 1;
    }
}

void destruct(PQ_T que)
{
    free(que->data);
    free(que->istoric);
    free(que);
}