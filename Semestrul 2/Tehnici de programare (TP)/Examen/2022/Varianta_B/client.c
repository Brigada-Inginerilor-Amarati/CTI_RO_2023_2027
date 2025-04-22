#include"pixel.h"
#include <stdio.h>

int main(void) {
    int n = 0;
    Pixel_t *pixeli = NULL;

    Pixel_t p1 = makePixel(10, 15, 255, 0, 0, 0.5);
    Pixel_t p2 = makePixel(20, 25, 0, 255, 0, 0.8);
    Pixel_t p3 = makePixel(30, 35, 0, 0, 255, 1.0);

    pixeli = addPixel(pixeli, &n, p1);
    pixeli = addPixel(pixeli, &n, p2);
    pixeli = addPixel(pixeli, &n, p3);

    printf("\n-----------------\nPixeli:\n----------------\n");
    printPixels(pixeli, n);

    Pixel_t mostOpaque = getMostOpaquePixel(pixeli, n);
    printf("\n-----------------\nCel mai opac pixel:\n----------------\n");
    printPixel(mostOpaque);

    printf("\n-----------------\nPixeli cu distanța până la origine între 0 și 50:\n----------------\n");
    int size = 0;
    Pixel_t *pixeliFiltrati = copyPixels(pixeli, n, 0.0, 50.0, &size);

    printPixels(pixeliFiltrati, size);

    freefiltrati(pixeliFiltrati, size + 1);
    freePixels(pixeli, n);
    

    return 0;
}