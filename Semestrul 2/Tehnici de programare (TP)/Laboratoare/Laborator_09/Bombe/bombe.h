#ifndef __BOMBE_H
#define __BOMBE_H

#include <stdio.h>
#include <stdlib.h>


typedef struct BOMB* Bomb_t;

//n - linii coordonate, k - indexul primei bombe care explodeaza
Bomb_t citeste_bombe_din_fisier(int *n, int *k, FILE *fin);

void print_bombe_info(Bomb_t bombe, int n);

void explozie(Bomb_t bombe, int n, int k, int *nr_bombe_explodate);
void print_bombe_info(Bomb_t bombe, int n);

#endif