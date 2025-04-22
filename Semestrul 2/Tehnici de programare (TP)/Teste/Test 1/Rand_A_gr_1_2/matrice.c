#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"

struct  Matrice
{
    Element_t **tablou;
    unsigned int linii_max;
    unsigned int coloane_max;
    unsigned int linii_curente;
    unsigned int coloane_curente;
};

struct Vector{
    unsigned int capacitate;
    Element_t *data;
};

Tab2D_t creeaza_tablou(unsigned int nr_linii, unsigned int nr_coloane)
{
    Tab2D_t matrice = malloc(sizeof(struct Matrice));
    Element_t **tablou=malloc(nr_linii * sizeof(Element_t*));

    for(unsigned int i = 0; i < nr_linii; i++)
    {
        tablou[i] = malloc(nr_coloane * sizeof(Element_t));
    }

    matrice->tablou = tablou;

    matrice->linii_max = nr_linii;
    matrice->coloane_max = nr_coloane;

    matrice->linii_curente = 0;
    matrice->coloane_curente = 0;

    for(unsigned int i = 0;i < matrice->linii_max; i++)
    {
        for(unsigned int j = 0; j < matrice->coloane_max; j++)
        {
            matrice->tablou[i][j] = 0;
        }
    }

    return matrice;
}
void afiseaza_matrice(Tab2D_t matrice)
{
    for(unsigned int i = 0;i < matrice->linii_curente; i++)
    {
        for(unsigned int j = 0; j < matrice->coloane_curente; j++)
        {
            printf("%d ", matrice->tablou[i][j]);
        }
        printf("\n");
    }
}

StatusCode_t atribuie_valoare(Tab2D_t matrice, unsigned int index_linie, unsigned int index_coloana, Element_t element_de_adaugat)
{
    if(index_linie < matrice->linii_max && index_coloana < matrice->coloane_max)
    {
        matrice->tablou[index_linie][index_coloana] = element_de_adaugat;

        if(index_linie >= matrice->linii_curente)
        {
            matrice->linii_curente = index_linie + 1;
        }
        if(index_coloana >= matrice->coloane_curente)
        {
            matrice->coloane_curente = index_coloana + 1;
        }

        return OK;
    }

    return EROARE_DEPASIRE_LIMITE;
}

Tab2D_t insumeaza_matrici(Tab2D_t matrice1, Tab2D_t matrice2)
{

    unsigned int linii_suma, coloane_suma;

    if(matrice1->linii_curente > matrice2->linii_curente)
    {
        linii_suma = matrice1->linii_curente;
    }
    else
    {
        linii_suma = matrice2->linii_curente;
    }

    if(matrice1->coloane_curente > matrice2->coloane_curente)
    {
        coloane_suma = matrice1->coloane_curente;
    }
    else
    {
        coloane_suma = matrice2->coloane_curente;
    }

    Tab2D_t matrice_suma = creeaza_tablou(linii_suma, coloane_suma);

    matrice_suma->linii_curente = linii_suma;
    matrice_suma->coloane_curente = coloane_suma;

    for(unsigned int i = 0; i < linii_suma; i++)
    {
        for(unsigned int j = 0; j < coloane_suma; j++)
        {
            matrice_suma->tablou[i][j] = matrice1->tablou[i][j] + matrice2->tablou[i][j];
        }
    }

    return matrice_suma;
}

Vector_t initializeaza_vector(unsigned int dimensiune)
{
    Vector_t vector = NULL;

    if((vector = malloc(sizeof(struct Vector))) == NULL)
    {
        vector->capacitate = 0;
        return NULL;
    }

    vector->capacitate = dimensiune;
    vector->data = malloc(dimensiune * sizeof(Element_t));

    if(vector->data == NULL)
    {
        perror("Vector alloc error");
        exit(-1);
    }

    return vector;
}

void afiseaza_vector(Vector_t vector)
{
    for(unsigned int i = 0; i < vector->capacitate; i++)
    {
        printf("%d ", vector->data[i]);
    }
    printf("\n");
}
int este_impar(Element_t element)
{
    return element % 2;
}
Vector_t copiaza(Tab2D_t matrice, int(*cond)(Element_t))
{
    Vector_t vector = initializeaza_vector(matrice->linii_curente * matrice->coloane_curente);
    int index = 0;
    for(unsigned int i = 0; i < matrice->linii_curente; i++)
    {
        for(unsigned int j = 0; j < matrice->coloane_curente; j++)
        {
            if(cond(matrice->tablou[i][j]))
            {
                vector->data[index] = matrice->tablou[i][j];
                index++;
            }
        }
    }
    vector->data = realloc(vector->data, (index) * sizeof(Element_t));

    vector->capacitate = index;
    return vector;
}