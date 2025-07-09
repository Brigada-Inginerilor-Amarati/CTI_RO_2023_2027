#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1
#define MAX_STUDENTI 100

typedef struct Student{
    char nume[50];
    char email[50];
}Student_T;

// sunt inserate dupa ID curs
typedef struct ArboreBinar{
    int IDCurs; // unic
    char denumireCurs[50];
    char profesor[50];
    Student_T student[MAX_STUDENTI];
    struct ArboreBinar *stanga;
    struct ArboreBinar *dreapta;
}ArboreBinar_T;

void initListaStudenti(Student_T *studenti, int nrStudenti){
    for(int i = 0; i < nrStudenti; i++){
        strcpy(studenti[i].nume, "");
        strcpy(studenti[i].email, "");
    }
}

ArboreBinar_T* initArbore(int IDCurs, char *denumireCurs, char *profesor){
    ArboreBinar_T *arbore = (ArboreBinar_T*)malloc(sizeof(ArboreBinar_T));

    if(arbore == NULL){
        printf("Eroare la alocarea memoriei pentru arbore.\n");
        return NULL;
    }

    arbore->IDCurs = IDCurs;
    strcpy(arbore->denumireCurs, denumireCurs);
    strcpy(arbore->profesor, profesor);
    initListaStudenti(arbore->student, MAX_STUDENTI);
    arbore->stanga = NULL;
    arbore->dreapta = NULL;

    return arbore;
}

ArboreBinar_T* adaugaCurs(ArboreBinar_T *radacina, int IDCurs, char *denumireCurs, char* profesor){
    if(radacina == NULL){
        return initArbore(IDCurs, denumireCurs, profesor);
    }

    if(IDCurs < radacina->IDCurs){
        radacina->stanga = adaugaCurs(radacina->stanga, IDCurs, denumireCurs, profesor);
    } else if(IDCurs > radacina->IDCurs){
        radacina->dreapta = adaugaCurs(radacina->dreapta, IDCurs, denumireCurs, profesor);
    } else {
        // Cursul cu acest ID deja exista
        printf("Cursul cu ID %d exista deja.\n", IDCurs);
    }

    return radacina;
}

void inordine(ArboreBinar_T *radacina){
    if(radacina == NULL){
        return;
    }

    inordine(radacina->stanga);
    printf("Curs ID: %d, Denumire: %s, Profesor: %s\n", radacina->IDCurs, radacina->denumireCurs, radacina->profesor);
    inordine(radacina->dreapta);
}

int main(int argc, char **argv){
    if(argc != 2){
        printf("Utilizare: %s <fisier_input>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if(f == NULL){
        printf("Eroare la deschiderea fisierului %s\n", argv[1]);
        return 1;
    }   

    ArboreBinar_T *radacina = NULL;
    int IDCurs;
    char denumireCurs[50], profesor[50];
    while(fscanf(f, "%d %49s %49s", &IDCurs, denumireCurs, profesor) == 3){
        radacina = adaugaCurs(radacina, IDCurs, denumireCurs, profesor);
    }

    fclose(f);

    printf("Cursuri in ordine crescatoare dupa ID:\n");
    inordine(radacina);
    return 0;
}