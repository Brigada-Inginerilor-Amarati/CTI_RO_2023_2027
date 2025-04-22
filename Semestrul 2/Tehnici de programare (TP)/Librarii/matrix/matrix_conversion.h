#ifndef __MATRIX_CONVERSION_H
#define __MATRIX_CONVERSION_H

#include "matrix_block.h"
#include "matrix_std.h"

void convert_matrix_to_block(matrix_std_t m, matrix_block_t b);

void convert_block_to_matrix(matrix_block_t b, matrix_std_t m);

#endif
