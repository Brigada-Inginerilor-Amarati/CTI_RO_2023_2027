#ifndef __MATRIX_OPERATIONS_H
#define __MATRIX_OPERATIONS_H

#include "matrix_data.h"
#include "matrix_std.h"

matrix_std_t add_matrix_std(matrix_std_t a, matrix_std_t b);

matrix_std_t multiply_matrix_std(matrix_std_t a, matrix_std_t b);

void rotate_matrix_std(matrix_std_t m, int option);

void sort_matrix_std(matrix_std_t m);

matrix_std_t transpose_matrix_std(matrix_std_t m);

#endif
