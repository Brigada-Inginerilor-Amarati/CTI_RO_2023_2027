#ifndef __MATRIX_H
#define __MATRIX_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_MATRIX_EL 10

typedef int Element_t;

typedef struct MATRIX* MatriceP_t;

MatriceP_t init_matrix(size_t);

void print_matrix(MatriceP_t);

void free_matrix(MatriceP_t);

MatriceP_t copy_matrix(MatriceP_t);

MatriceP_t oglindit(MatriceP_t);

int check_secondary_diagonal(MatriceP_t, int (*)(Element_t));

void assign_random_values(MatriceP_t);

Element_t * get_negative_elements(MatriceP_t x, size_t *count);

#endif