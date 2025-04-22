#ifndef __MATRIX_STD_H
#define __MATRIX_STD_H

#include "matrix_data.h"

matrix_std_t init_matrix_std(matrix_size_t rows, matrix_size_t collumns);

void read_data_matrix_std(matrix_std_t matrix, FILE *file);

void print_matrix_std(matrix_std_t matrix, FILE *file);

void free_matrix_std(matrix_std_t matrix);

matrix_data_t quadrant_sum_matrix_std(matrix_std_t matrix, int option);

#endif
