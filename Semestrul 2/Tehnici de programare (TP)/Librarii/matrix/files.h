#ifndef __FILES_H
#define __FILES_H

#include <stdio.h>
#include <stdlib.h>

FILE *open_file(const char *filename, const char *mode);

void close_file(FILE *file);

void reset_file(const char *filename);

#endif
