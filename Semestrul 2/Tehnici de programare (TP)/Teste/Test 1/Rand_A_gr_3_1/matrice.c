#include "matrice.h"

struct MATRIX {
    Element_t **date;
    size_t n;
};


MatriceP_t init_matrix(size_t n)
{
    // alocarea matricii

    MatriceP_t x = (MatriceP_t) malloc (sizeof(struct MATRIX));

    if(x == NULL)
    {
        perror("Matrix malloc error");
        return NULL;
    }

    *x = (struct MATRIX) {NULL, n};

    // alocarea liniilor

    x->date = (Element_t **) malloc(n * sizeof(Element_t *));

    if(x->date == NULL)
    {
        perror("Matrix lines malloc error");
        return NULL;
    }

    // alocarea coloanelor

    for(size_t i = 0; i < n; i++)
    {
        x->date[i] = (Element_t *) malloc(n * sizeof(Element_t));

        if(x->date[i] == NULL)
        {
            perror("Matrix columns malloc error");
            return NULL;
        }

        // initializare valori

        for(size_t j = 0; j < n; j++)
            x->date[i][j] = 0;
    }
        
    return x;
}


void assign_random_values(MatriceP_t x)
{
    for(size_t i = 0; i < x->n; i++)
        for(size_t j = 0; j < x->n; j++)
        {
            if(rand() % 2)
                x->date[i][j] = -1 * rand() % MAX_MATRIX_EL;
            else
                x->date[i][j] = rand() % MAX_MATRIX_EL;
        }
            
}


void print_matrix(MatriceP_t x)
{
    for(size_t i = 0; i < x->n; i++)
    {
        for(size_t j = 0; j < x->n; j++)
            printf("%d ", x->date[i][j]);

        printf("\n");
    }
}


void free_matrix(MatriceP_t x)
{
    for(size_t i = 0; i < x->n; i++)
        free(x->date[i]);

    free(x->date);
    free(x);
}


MatriceP_t copy_matrix(MatriceP_t main)
{
    MatriceP_t copy = init_matrix(main->n);

    for(size_t i = 0; i < main->n; i++)
        for(size_t j = 0; j < main->n; j++)
            copy->date[i][j] = main->date[i][j];

    return copy;
}


MatriceP_t oglindit(MatriceP_t main)
{
    MatriceP_t ogl = copy_matrix(main);

    for(size_t i = 0; i < ogl->n; i++)
    {
        for(size_t j = 0; j < ogl->n / 2 ; j++)
        {
            Element_t aux = ogl->date[i][j];
            ogl->date[i][j] = ogl->date[i][ogl->n - j - 1];
            ogl->date[i][ogl->n - j - 1] = aux;
        }
            
    }
    
    return ogl;
}


Element_t * get_negative_elements(MatriceP_t x, size_t *count)
{
    Element_t * negatives = (Element_t *) malloc(x->n * x->n * sizeof(Element_t));

    size_t index = 0;

    for(size_t i = 0; i < x->n; i++)
        for(size_t j = 0; j < x->n; j++)
            if(x->date[i][j] < 0)
                negatives[index++] = x->date[i][j];

    *count = index;
    return negatives;
}


int check_secondary_diagonal(MatriceP_t x, int (*predicat)(Element_t))
{
    for(size_t i = 0; i < x->n; i++)
        if(!predicat(x->date[i][x->n - i - 1]))
            return 0;
    
    return 1;
}