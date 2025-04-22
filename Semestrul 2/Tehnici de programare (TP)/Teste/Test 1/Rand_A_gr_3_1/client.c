#include "matrice.h"
#include <time.h>
#define MATRIX_SIZE 4

int is_positive(Element_t el)
{
    return el > 0;
}

void print_vector(Element_t *vector, size_t count)
{
    for(size_t i = 0; i < count; i++)
        printf("%d ", vector[i]);
    printf("\n");
}

int main(void)
{

    srand(time(NULL));

    MatriceP_t x = init_matrix(MATRIX_SIZE);
    

    assign_random_values(x);

    printf("ORIGINALA:\n");
    print_matrix(x);


    MatriceP_t cpy = oglindit(x);

    printf("OGLINDITA:\n");
    print_matrix(cpy);


    printf("VERIFICARE CONDITIE COLOANA:\n");

    if(check_secondary_diagonal(x, is_positive))
        printf("True\n");
    else
        printf("False\n");


    
    size_t count = 0;
    Element_t *neg = get_negative_elements(x, &count);

    printf("VERIFICARE NUMERE NEGATIVE:\n");
    print_vector(neg, count);

    free_matrix(x);
    free_matrix(cpy);
    free(neg);

    return 0;
}