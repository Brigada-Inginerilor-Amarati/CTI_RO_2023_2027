#ifndef __SPECTACOLE_H
#define __SPECTACOLE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int start_hour;
    int end_hour;
}Spectacol_t;

Spectacol_t* citeste_ore(FILE *fin, int *n);
void print_data(Spectacol_t *spectacole, int n);
int cmp_end_hour(const void *a, const void *b);
int alege_spectacole(Spectacol_t *spectacole, int n);

#endif