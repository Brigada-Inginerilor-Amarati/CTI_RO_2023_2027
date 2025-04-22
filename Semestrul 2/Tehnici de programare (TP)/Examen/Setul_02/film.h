#ifndef _FILME_H
#define _FILME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Film* Film_t;
typedef struct Site* Site_t;



Site_t adaugare (Site_t, char*, char*, int, int);
void afisareFilme (Site_t);

void afisareMaxim(Site_t site);

#endif