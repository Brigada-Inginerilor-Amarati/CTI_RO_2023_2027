#include "film.h"

#define MAX_LENGTH 41
#define CAP 20

char genuri[4][30] = {"actiune", "comedie", "romance", "thriller"};

struct Film {
    char nume[MAX_LENGTH];
    int durata;
    int cost;
    char gen[MAX_LENGTH];
};

struct Site {
    Film_t* filme;
    unsigned n;
};

Site_t makeSite () {
    Site_t site;
    if ((site = malloc(sizeof(struct Site))) == NULL)
        return NULL;
    
    Film_t* film;
    if ((film = malloc(CAP * sizeof(Film_t))) == NULL)
        return NULL;
    site->filme = film;

    site->n = 0;
    return site;
}

Site_t adaugare (Site_t site, char* nume, char* gen, int durata, int cost) {
    if (!site)
        site = makeSite();

    if (site->n > CAP - 1) {
        printf("Spatiu insuficient!\n");
        return site;
    }

    Film_t film;
    if ((film = malloc(sizeof(struct Film))) == NULL)
        return NULL;
    
    strcpy(film->nume, nume);
    film->durata = durata;
    film->cost = cost;
    strcpy(film->gen, gen);
    
    site->filme[site->n ++] = film;

    return site;
}

int cmp (const void* elem1, const void* elem2) {
    const Film_t el1 = *(const Film_t*)elem1;
    const Film_t el2 = *(const Film_t*)elem2;
    if ((float)el1->cost / el1->durata < (float)el2->cost / el2->durata)
        return 1;
    if ((float)el1->cost / el1->durata > (float)el2->cost / el2->durata)
        return -1;
    return 0;
    
}

void afisareFilme (Site_t site) {
    qsort(site->filme, site->n, sizeof(Film_t), cmp);

    for (unsigned i = 0; i < site->n; i ++)
        printf("%s; %d; %d; %s\n", site->filme[i]->nume, site->filme[i]->durata, site->filme[i]->cost, site->filme[i]->gen);
}

int cmp2(const void* elem1, const void* elem2) {
    const Film_t el1 = *(const Film_t*)elem1;
    const Film_t el2 = *(const Film_t*)elem2;

    if (el1->durata < el2->durata)
        return 1;
    if (el1->durata > el2->durata)
        return -1;
    return 0;
}


void afisareMaxim(Site_t site) {
    qsort(site->filme, site->n, sizeof(Film_t), cmp2);

    printf("\n-------------\n");
    for (unsigned i = 0; i < site->n; i ++)
        printf("%s; %d; %d; %s\n", site->filme[i]->nume, site->filme[i]->durata, site->filme[i]->cost, site->filme[i]->gen);


    for (int i = 0; i < 4; i++) {
        int found = 0;
        for (unsigned j = 0; j < site->n; j++) {
            if (strstr(site->filme[j]->gen, genuri[i])) {
                printf("%s: %s\n", genuri[i], site->filme[j]->nume);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("%s: nu există filme în acest gen\n", genuri[i]);
        }
    }
}

