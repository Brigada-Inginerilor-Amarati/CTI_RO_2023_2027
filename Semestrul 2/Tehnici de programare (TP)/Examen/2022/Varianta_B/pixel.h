#ifndef __PIXEL_H
#define __PIXEL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct CULOARE *Culoare_t;

typedef struct PIXEL *Pixel_t;

Pixel_t makePixel(int x, int y, int r, int g, int b, double alpha);

Pixel_t *addPixel(Pixel_t *v_pixeli, int *n, Pixel_t pixel_to_add);

Pixel_t getMostOpaquePixel(Pixel_t v[], int n);

Pixel_t* copyPixels(Pixel_t v[], int n, double dMin, double dMax, int *size);

void printPixel(Pixel_t p);

void printPixels(Pixel_t v[], int n);

void freePixels(Pixel_t *v, int n);

void freefiltrati(Pixel_t *p, int size);




#endif