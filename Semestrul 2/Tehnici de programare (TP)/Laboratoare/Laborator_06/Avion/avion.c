#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avion.h"

struct Pasager{
    char nume[41];
    float greutate;
    int categorie;
};

struct Avion{
    Pasager_t *Categoria_1;
    Pasager_t *Categoria_2;
    unsigned int nr_locuri_categoria_1;
    unsigned int nr_locuri_categoria_2;

    unsigned int sp_cat_1;
    unsigned int sp_cat_2;
};

Avion_t* makeAvion(unsigned int nr_categoria_1, unsigned int nr_categoria_2)
{
    Avion_t *avion = NULL;

    if((avion = malloc(sizeof(struct Avion))) == NULL)
    {
        return NULL;
    }

    avion->Categoria_1 = malloc(nr_categoria_1 * sizeof(struct Pasager));
    avion->Categoria_2 = malloc(nr_categoria_2 * sizeof(struct Pasager));

    avion->nr_locuri_categoria_1 = nr_categoria_1;
    avion->nr_locuri_categoria_2 = nr_categoria_2;
    avion->sp_cat_1 = 0;
    avion->sp_cat_2 = 0;

    return avion;
}

Avion_t* adaugare(Avion_t* a, char* nume, int gr_b, int nr_cat)
{
    switch (nr_cat)
    {
    case 1:
        if(a -> sp_cat_1 == a -> nr_locuri_categoria_1)
        {
            printf("Nu mai sunt locuri la categroia %d. \n", nr_cat);
            return a;
        }

        Pasager_t pasager_nou;
        strcpy(pasager_nou.nume, nume);
        pasager_nou.greutate = gr_b;
        pasager_nou.categorie = nr_cat;

        a->Categoria_1[a->sp_cat_1] = pasager_nou;

        a->sp_cat_1++; 
        break;
    
    case 2:
        if(a -> sp_cat_2 == a -> nr_locuri_categoria_2)
        {
            printf("Nu mai sunt locuri la categroia %d. \n", nr_cat);
            return a;
        }

        Pasager_t pasager;
        strcpy(pasager.nume, nume);
        pasager.greutate = gr_b;
        pasager.categorie = nr_cat;

        a->Categoria_2[a->sp_cat_2] = pasager;

        a->sp_cat_2++; 
        break;
    
    default:
        break;
    }

    return a;
}

int compararePasageri(const void *a, const void *b)
{
    const Pasager_t *pasager1 = (const Pasager_t*) a;
    const Pasager_t *pasager2 = (const Pasager_t*) b;

    return strcmp(pasager1->nume, pasager2->nume);
}

void afisarePasageri(Avion_t* avion, int g)
{
   Pasager_t pasageri[avion->sp_cat_1 + avion->sp_cat_2];
   int nr_pasageri_totali = 0;

   for(unsigned int i = 0; i < avion->sp_cat_1; i++)
   {
    if(avion->Categoria_1[i].greutate > g)
    {
        pasageri[nr_pasageri_totali++] = avion->Categoria_1[i];
    }
   }

   for(unsigned int i = 0; i < avion->sp_cat_2; i++)
   {
    if(avion->Categoria_2[i].greutate > g)
    {
        pasageri[nr_pasageri_totali++] = avion->Categoria_2[i];
    }
   }

   qsort(pasageri, nr_pasageri_totali, sizeof(Pasager_t), compararePasageri);

   printf("\nPasageri sortati alfabetic care au bagaj cu o greutate mai mare decat %d \n", g);

   for(unsigned int i = 0; i < nr_pasageri_totali; i++)
   {
    printf("\nNume pasager %s, ", pasageri[i].nume);
    printf(" greutate bagaj: %f", pasageri[i].greutate);
    printf(", categoria : %d \n", pasageri[i].categorie);
   }

}

int mutarePasageri(Avion_t *avion, int x, int nr_cat)
{
    int nr_pasageri_mutati = 0;


    switch (nr_cat)
    {
        case 1:
            if(x > avion-> nr_locuri_categoria_1)
            {
                return 0;
            }
            if(x <= 0)
            {
                return 0;
            }
            while (x > 0 && avion->sp_cat_2 < avion -> nr_locuri_categoria_2)
            {
                avion->Categoria_1[avion->sp_cat_1 - 1].categorie = 2;
                avion->Categoria_2[avion->sp_cat_2] = avion->Categoria_1[avion->sp_cat_1 - 1];

                avion->sp_cat_2++;
                avion->sp_cat_1--;
                nr_pasageri_mutati ++;
                x--;
            }
            
            break;
        case 2:
        if(x > avion-> nr_locuri_categoria_2)
            {
                return 0;
            }
        if(x <= 0)
            {
                return 0;
            }
            while (x > 0 && avion->sp_cat_1 < avion -> nr_locuri_categoria_1)
            {
                avion->Categoria_2[avion->sp_cat_2 - 1].categorie = 1;
                avion->Categoria_1[avion->sp_cat_1] = avion->Categoria_2[avion->sp_cat_2 - 1];

                avion->sp_cat_1++;
                avion->sp_cat_2--;
                nr_pasageri_mutati ++;
                x--;
            }

            break;
        default:
            break;
    }

    return nr_pasageri_mutati;
}