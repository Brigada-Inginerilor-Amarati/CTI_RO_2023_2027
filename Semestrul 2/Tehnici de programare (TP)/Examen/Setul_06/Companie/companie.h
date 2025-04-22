#ifndef __COMP_H
#define __COMP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 40
#define ANGAJATI_CAP 20
#define ANG_COMP_CAP 100
#define PROJECT_CAP 20

typedef enum {SOFTWARE, TESTARE, MANAGEMENT} Departament_t;

typedef enum {HIGH_PRIORITY, MEDIUM_PRIORITY, LOW_PRIORITY} Prioritate_t;

typedef struct ANGAJAT *Angajat_t;

typedef struct PROIECT *Proiect_t;

typedef struct COMPANIE *Companie_t;

//functii de creare aditionale

Angajat_t create_angajat(char *name, Departament_t cod_departament, Proiect_t proiect);

Proiect_t create_proiect(char *name, Prioritate_t priority);

Companie_t create_companie(const char* name);

//functii de adaugare aditionale

void add_angajat_to_proiect(Proiect_t proiect, Angajat_t angajat_to_add);

void add_angajat_to_companie(Companie_t companie, Angajat_t angajat_to_add);

void add_proiect_to_companie(Companie_t companie, Proiect_t proiect_to_add);

//functii de printare info aditionale

void printAngajat(Angajat_t angajat);

void printProiect(Proiect_t proiect);

void printCompanie(Companie_t companie);

//functii de eliberare memorie 

void freeAngajat(Angajat_t angajat);

void freeProiect(Proiect_t proiect);

void freeCompanie(Companie_t companie);

void free_vectorAngajati(Angajat_t *angajati, int n);

//cerinta

void print_angajati_sortati(Proiect_t Proiect);

Angajat_t* sort_angajati_by_name(Angajat_t *angajati, int n);

Angajat_t *gaseste_angajati_dupa_departament_prioritate(Companie_t companie, Departament_t departament, Prioritate_t prioritate, int *size);


#endif