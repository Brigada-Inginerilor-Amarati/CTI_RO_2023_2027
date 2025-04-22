#include "companie.h"

struct ANGAJAT{
    char nume_angajat[MAX_NAME_LEN];
    Departament_t cod_Departament;
    Proiect_t proiect_la_care_lucreaza;
};

struct PROIECT{
    char nume_proiect[MAX_NAME_LEN];
    Angajat_t *angajati;
    int count_angajati;
    Prioritate_t prioritate_proiect;
};


struct COMPANIE{
    char nume_companie[MAX_NAME_LEN];
    Angajat_t *angajati;
    int count_angajati_comp;
    Proiect_t *proiecte;
    int proiecte_count;
};

Angajat_t create_angajat(char *name, Departament_t cod, Proiect_t proiect){
    Angajat_t angajat_creat = malloc(sizeof(struct ANGAJAT));

    if(angajat_creat == NULL){
        printf("eroare creare angajat \n"); 
        return NULL;
    }

    strncpy( angajat_creat->nume_angajat, name, MAX_NAME_LEN - 1);
    angajat_creat->nume_angajat[MAX_NAME_LEN - 1] = '\0';

    angajat_creat->cod_Departament = cod;
    angajat_creat->proiect_la_care_lucreaza = proiect;

    return angajat_creat;
}

Proiect_t create_proiect(char *name, Prioritate_t priority){
    Proiect_t proiect_creat = malloc(sizeof(struct PROIECT));

    if(proiect_creat == NULL){
        printf("eroare la crearea proiectului \n");
    }

    strcpy(proiect_creat->nume_proiect, name);
    proiect_creat->prioritate_proiect = priority;

    proiect_creat->count_angajati = 0;

    proiect_creat->angajati = malloc(ANGAJATI_CAP * sizeof(Angajat_t));

    if(proiect_creat->angajati == NULL){
        printf("eroare alocare memorie angajati proiect \n");
        free(proiect_creat);
        return NULL;
    } 

    return proiect_creat;
}

Companie_t create_companie(const char* name){
    Companie_t companie_creata = malloc(sizeof(struct COMPANIE));

    if(companie_creata == NULL){
        printf("eroare la crearea companiei \n");
        return NULL;
    }

    strncpy(companie_creata->nume_companie, name, MAX_NAME_LEN - 1);
    companie_creata->nume_companie[MAX_NAME_LEN - 1] = '\0';

    companie_creata->count_angajati_comp = 0;
    companie_creata->proiecte_count = 0;

    companie_creata->angajati = malloc(ANG_COMP_CAP * sizeof(Angajat_t));
    if(companie_creata->angajati == NULL){
        printf("eroare alocare memorie angajati companie \n");
        free(companie_creata);
        return NULL;
    }

    companie_creata->proiecte = malloc(PROJECT_CAP * sizeof(Proiect_t));

    if(companie_creata->proiecte == NULL){
        printf("eroare alocare memorie proiecte companie \n");
        free(companie_creata->angajati);
        free(companie_creata);
        return NULL;
    }

    return companie_creata;
}

void add_angajat_to_proiect(Proiect_t proiect, Angajat_t angajat_to_add){
    if(proiect->count_angajati < ANGAJATI_CAP){
        proiect->angajati[proiect->count_angajati++] = angajat_to_add;
    }
    else{
        printf("Proiectul este plin \n");
    }
}

void add_angajat_to_companie(Companie_t companie, Angajat_t angajat_to_add){
    if(companie->count_angajati_comp < ANG_COMP_CAP){
        companie->angajati[companie->count_angajati_comp++] = angajat_to_add; 
    }
    else{
        printf("Compania este plina \n");
    }
    
}

void add_proiect_to_companie(Companie_t companie, Proiect_t proiect_to_add){
    if(companie->proiecte_count < PROJECT_CAP){
        companie->proiecte[companie->proiecte_count++] = proiect_to_add;
    }
    else{
        printf("Nu mai pot fi adaugate proiecte \n");
    }
}

void printAngajat(Angajat_t angajat){
    if(angajat){
        printf("Nume : %s - Departament: %d - Proiect : %s\n", angajat->nume_angajat, angajat->cod_Departament, angajat->proiect_la_care_lucreaza->nume_proiect);
    }
}

void printProiect(Proiect_t proiect){
    if(proiect){
        printf("Proiect : %s - Prioritate : %d - Angajatii care lucreaza la el : \n", proiect->nume_proiect, proiect->prioritate_proiect);
        for(int i = 0; i < proiect->count_angajati; i++){
            printf("Nume angajat : %s \n", proiect->angajati[i]->nume_angajat);
        }
    }
}

void printCompanie(Companie_t companie){
    if(companie){
        printf("Nume companie : %s - Proiectele din companie : \n", companie->nume_companie);

        for(int i = 0; i < companie->proiecte_count; i++){
            printProiect(companie->proiecte[i]);
        }
    }
}

void freeAngajat(Angajat_t angajat){
    if(angajat){
        free(angajat);
    }
}

void freeProiect(Proiect_t proiect){
    if(proiect){
        for(int i = 0; i < proiect->count_angajati; i++){
            freeAngajat(proiect->angajati[i]);
        }
        free(proiect->angajati);
        free(proiect);
    }
}

void freeCompanie(Companie_t companie){
    if(companie){
        for(int i = 0; i < companie->proiecte_count; i++){
            freeProiect(companie->proiecte[i]);
        }
        free(companie->angajati);
        free(companie->proiecte);
        free(companie);
    }
}

int cmp(const void *a, const void *b){
    Angajat_t p1 = *(Angajat_t *) a;
    Angajat_t p2 = *(Angajat_t *) b;

    return strcmp(p1->nume_angajat, p2->nume_angajat); 
}

Angajat_t* sort_angajati_by_name(Angajat_t *angajati, int n){
    qsort(angajati, n, sizeof(Angajat_t), cmp);

    return angajati;
}

void print_angajati_sortati(Proiect_t Proiect){
    Proiect->angajati = sort_angajati_by_name(Proiect->angajati, Proiect->count_angajati); 

    printProiect(Proiect);
}

Angajat_t *gaseste_angajati_dupa_departament_prioritate(Companie_t companie, Departament_t departament, Prioritate_t prioritate, int *size){
    Angajat_t *angajati_gasiti = NULL;
    *size = 0;

    for(int i = 0; i < companie->count_angajati_comp;i++){
        if(companie->angajati[i]->cod_Departament == departament && companie->angajati[i]->proiect_la_care_lucreaza->prioritate_proiect == prioritate){
            (*size)++;
        }
    }

    angajati_gasiti = malloc(*size * sizeof(Angajat_t));

    if (angajati_gasiti == NULL)
    {
        printf("Eroare la alocarea memoriei pt angajatii gasiti \n");
        return NULL;
    }
    
    int index = 0;
    for(int i = 0; i < companie->count_angajati_comp;i++){
        if(companie->angajati[i]->cod_Departament == departament && companie->angajati[i]->proiect_la_care_lucreaza->prioritate_proiect == prioritate){
            angajati_gasiti[index++] = companie->angajati[i];
        }
    }

    angajati_gasiti = sort_angajati_by_name(angajati_gasiti, *size);
    
    for(int i = 0; i < *size; i++){
        printAngajat(angajati_gasiti[i]);
    }

    return angajati_gasiti;
}

void free_vectorAngajati(Angajat_t *angajati, int n){
    // for(int i = 0; i < n; i++){
    //     free(angajati[i]);
    // }

    free(angajati);
}