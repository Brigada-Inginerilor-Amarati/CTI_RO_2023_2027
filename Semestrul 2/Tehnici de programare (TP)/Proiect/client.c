#include "rand_array.h"
#include <time.h>

// PROIECT 1

// numar de elemente vectori
#define SIZE 10

// Rand limit parameters

#define LOWER_LIMIT 0
#define UPPER_LIMIT 100

//RAND FLEX ARRAY

#define STEPS 13
#define FLEX_INTERVAL 1000

//PROIECT 2

// Parametrii distributii

#define N_ELEM 1000
#define MEDIA 0.0
#define ABATERE_STANDARD 1
#define LAMBDA 1



void print_unsigned_Array(FILE *fout, unsigned *array, unsigned n)
{
    for(size_t i = 0; i < n; i++)
    {
        fprintf(fout, "v[%ld] = %u \n", i, array[i]);
    }

    fprintf(fout, "\n");
}

void print_int_array(FILE *fout,int *array, unsigned n)
{
    for(size_t i = 0; i < n; i++)
    {
        fprintf(fout, "v[%ld] = %d \n", i, array[i]);
    }

    fprintf(fout, "\n");
}

void do_random_array(FILE *fout, unsigned size){
    //ne cream vectorul cu numere random
    unsigned *rand_array = makeRandArray(size);

    fprintf(fout, "Vectorul cu numere pseudo aleatoare : \n");

    //printam datele in fisierul de iesire
    print_unsigned_Array(fout, rand_array, size);

    //eliberam memoria alocata pentru vector
    free(rand_array);
}

void do_random_limit_array(FILE *fout, unsigned size, int lower_limit, int upper_limit){
    // cream vectorul
    int *random_limit_array = makeRandLimitArray(size, lower_limit, upper_limit);

    fprintf(fout, "\n \nVectorul cu numere pseudo aleatoare intre %d si %d: \n", lower_limit, upper_limit);

    print_int_array(fout, random_limit_array, size);

    free(random_limit_array);
}

// pt task 3

int getIncreasing(int *array, unsigned n)
{
    if(n == 0)
    {
        return rand() % FLEX_INTERVAL;
    }

    return array[n-1] + rand() % FLEX_INTERVAL + STEPS;
}

int getDecreasing(int *array, unsigned n)
{
    if(n == 0)
    {
        return rand() % FLEX_INTERVAL;
    }

    return array[n-1] - rand() % FLEX_INTERVAL - STEPS;
}

void do_random_flex_array_asc(FILE *fout, unsigned size){
    int *rand_asc_array = makeRandFlexiArray(size, getIncreasing);

    fprintf(fout, "\n \nVectorul cu numere pseudo aleatoare in ordine crescatoare: \n");

    print_int_array(fout, rand_asc_array, size);

    free(rand_asc_array);
}

void do_random_flex_array_desc(FILE *fout, unsigned size){
    int *rand_desc_array = makeRandFlexiArray(size, getDecreasing);

    fprintf(fout, "\n \nVectorul cu numere pseudo aleatoare in ordine descrescatoare: \n");

    print_int_array(fout, rand_desc_array, size);

    free(rand_desc_array);
}

void makeProiect1(char *nume_fisier, unsigned size){
    FILE *fout = fopen(nume_fisier, "w");

    if(fout == NULL){
        printf("eroare deschidere fisier \n");
        return ;
    }

    do_random_array(fout, size);

    do_random_limit_array(fout, size, LOWER_LIMIT, UPPER_LIMIT);

    do_random_flex_array_asc(fout, size);

    do_random_flex_array_desc(fout, size);


    fclose(fout);
}

void makeProiect2(char *nume_fisier_gauss, char *nume_fisier_poisson, unsigned size){
    FILE *gauss = fopen(nume_fisier_gauss, "w");

    if(gauss == NULL){
        printf("eroare deschidere fisier gauss\n");
        return ;
    }

    FILE *poisson = fopen(nume_fisier_poisson, "w");

    if(poisson == NULL){
        printf("eroare deschidere fisier poisson\n");
        return ;
    }

    for(int i = 0; i < N_ELEM; i++){
        fprintf(gauss, "%.3g \n", generate_normalDistribution(0, 1));
    }

    for(int i = 0; i < N_ELEM; i++){
        fprintf(poisson,"%d \n", generate_poissonDistribution(10));
    }

    fclose(gauss);
    fclose(poisson);
}

int main(int argc, char **argv){
    if(argc != 4){
        printf("Incorrect ussage of arguments. This program requires 3 filepaths \n");
    }

    srand(time(NULL));

    int optiune = 0;


    printf("Optiunile din acest program sunt : \nPentru executie Proiect 1 - introduceti 1\nPentru executie Proiect 2 - introduceti 2\nPentru executie ambele proiecte - introduceti 3\n\n");

    scanf("%d", &optiune);

    switch (optiune)
    {
    case 1:
        makeProiect1(argv[1], SIZE);
        break;
    case 2:
        makeProiect2(argv[2], argv[3], N_ELEM);
        break;
    case 3:
        makeProiect1(argv[1], SIZE);
        makeProiect2(argv[2], argv[3], N_ELEM);
        break;
    default:
        printf("Optiune invalida\n");
        break;
    }

    return 0;
}