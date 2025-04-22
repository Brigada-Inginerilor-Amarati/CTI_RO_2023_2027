#include "esantion.h"

int main(void){
    int n = 0;

    Esantion_t *esantioane = NULL;

    Esantion_t e1 = makeEsantion(23.5, 12, 40, 26, 13, "Insorit");
    Esantion_t e2 = makeEsantion(10, 5, 30, 16, 4, "Frig noaptea");
    Esantion_t e3 = makeEsantion(30.7, 16, 20, 13, 10, "Extrem de cald");

    esantioane = addSample(esantioane, &n, e1);
    esantioane = addSample(esantioane, &n, e2);
    esantioane = addSample(esantioane, &n, e3);

    printf("\n-----------------\nEsantioane:\n----------------\n");

    printEsantioante(esantioane, n);

    Esantion_t max = getMaxTemp(esantioane, n);

    printf("\n-----------------\nMax Temp Sample:\n----------------\n");

    printEsantion(max);

    printf("\n-----------------\nEsantioane cu temp cuprinse intre 0 si 30 de grade:\n----------------\n");

    int size = 0;
    Esantion_t *filtrate = copySamples(esantioane, n, 0.0, 30.0, &size);

    printEsantioante(filtrate, size);

    freeEsantioanefiltrate(filtrate, size);
    freeEsantioane(esantioane, n);
    //freeEsantioane(filtrate, size);

    return 0;
}