#ifndef __ESANTION_H
#define __ESANTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

typedef struct ESANTION *Esantion_t;

typedef struct LOCATIE *Locatie_t;

Esantion_t makeEsantion(double value, int ora, int grd, int min, int sec, const char *comm);

Esantion_t* addSample(Esantion_t *t, int *n, Esantion_t e);

Esantion_t getMaxTemp(Esantion_t *esantioane, int n);

Esantion_t *copySamples(Esantion_t v[], int n, double tMin, double tMax, int *size);

void printEsantion(Esantion_t esantion);

void printEsantioante(Esantion_t *esantioane, int n);

void freeEsantion(Esantion_t esantion);

void freeEsantioane(Esantion_t *esantioane, int n);

void freeEsantioanefiltrate(Esantion_t *p, int size);

#endif