#ifndef __MATRIX_DATA_H
#define __MATRIX_DATA_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef double matrix_data_t;
typedef size_t matrix_size_t;

typedef struct
{
  matrix_size_t rows, collumns;
  matrix_data_t **data;
} matrix_std_t;

typedef struct
{
  matrix_size_t rows, collumns;
  matrix_data_t *data;
} matrix_block_t;

#endif
