#include "pixel.h"

struct CULOARE {
    int r;
    int g;
    int b;
};

struct PIXEL {
    int x;
    int y;
    Culoare_t culoare;
    double alpha;
};

Pixel_t makePixel(int x, int y, int r, int g, int b, double alpha) {
    Pixel_t pixel = malloc(sizeof(struct PIXEL));
    if (pixel == NULL) {
        printf("error\n");
        return NULL;
    }

    pixel->culoare = malloc(sizeof(struct CULOARE));
    if (pixel->culoare == NULL) {
        printf("error\n");
        free(pixel);
        return NULL;
    }

    pixel->x = x;
    pixel->y = y;
    pixel->culoare->r = r;
    pixel->culoare->g = g;
    pixel->culoare->b = b;
    pixel->alpha = alpha;

    return pixel; 
}

Pixel_t *addPixel(Pixel_t *v_pixeli, int *n, Pixel_t pixel_to_add) {
    Pixel_t *aux = realloc(v_pixeli, ((*n) + 1) * sizeof(Pixel_t));
    if (aux == NULL) {
        printf("mem\n");
        return v_pixeli;
    }
    v_pixeli = aux;
    v_pixeli[*n] = pixel_to_add;
    (*n)++;
    return v_pixeli;
}

Pixel_t getMostOpaquePixel(Pixel_t v[], int n) {
    Pixel_t mostOpaque = v[0];
    for (int i = 1; i < n; i++) {
        if (v[i]->alpha > mostOpaque->alpha ||
           (v[i]->alpha == mostOpaque->alpha && 
            (abs(v[i]->x) + abs(v[i]->y)) < (abs(mostOpaque->x) + abs(mostOpaque->y)))) {
            mostOpaque = v[i];
        }
    }
    return mostOpaque;
}

double distanceFromOrigin(Pixel_t p) {
    return sqrt(p->x * p->x + p->y * p->y);
}

Pixel_t* copyPixels(Pixel_t v[], int n, double dMin, double dMax, int *size) {
    Pixel_t *result = NULL;
    int count = 0;
    for (int i = 0; i < n; i++) {
        double dist = distanceFromOrigin(v[i]);
        if (dist >= dMin && dist <= dMax) {
            Pixel_t *aux = realloc(result, (count + 1) * sizeof(Pixel_t));
            if (aux == NULL) {
                printf("Eroare la realocarea memoriei pentru pixeli.\n");
                free(result);
                return NULL;
            }
            result = aux;
            result[count++] = v[i];
        }
    }

    Pixel_t end = makePixel(-1, -1, 0, 0, 0, 0.0);
    if (end == NULL) {
        printf("Eroare la crearea pixelului end.\n");
        free(result);
        return NULL;
    }
    Pixel_t *aux = realloc(result, (count + 1) * sizeof(Pixel_t));
    if (aux == NULL) {
        printf("Eroare la realocarea memoriei pentru pixeli.\n");
        free(result);
        return NULL;
    }

    result = aux;
    result[count] = end;
    *size = count;
    return result;
}

void printPixel(Pixel_t p) {
    if (p) {
        printf("Pixel(x: %d, y: %d, R: %d, G: %d, B: %d, alpha: %.2f)\n", 
               p->x, p->y, p->culoare->r, p->culoare->g, p->culoare->b, p->alpha);
    }
}

void printPixels(Pixel_t v[], int n) {
    for (int i = 0; i < n; i++) {
        printPixel(v[i]);
    }
    printf("\n");
}

void freePixels(Pixel_t *v, int n) {
    for (int i = 0; i < n; i++) {
        free(v[i]->culoare);
        free(v[i]);
    }
    free(v);
}

void freefiltrati(Pixel_t *p, int size){
    free(p[size - 1]->culoare);
    free(p[size - 1]);
    free(p);
}