#ifndef __MATRIX_BLOCK_H
#define __MATRIX_BLOCK_H

#include "matrix_data.h"

matrix_block_t init_matrix_block(matrix_size_t rows, matrix_size_t collumns);

void read_matrix_block_data(matrix_block_t b, FILE *input_file);

void print_matrix_block(matrix_block_t b, FILE *output_file);

void free_matrix_block(matrix_block_t b);

matrix_data_t sum_matrix_block(matrix_block_t b);

#endif
