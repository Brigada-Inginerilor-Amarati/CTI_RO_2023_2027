#include "spectacole.h"

Spectacol_t* citeste_ore(FILE *fin, int *n){
    int x, y;
    Spectacol_t *spectacole = malloc(sizeof(Spectacol_t));
    int i = 0;
    while(fscanf(fin, "%d %d", &x, &y) != EOF){

        Spectacol_t *temp = realloc(spectacole, (i + 1) * sizeof(Spectacol_t));
            if (temp == NULL) {
                free(spectacole); // Eliberăm memoria alocată anterior
                fprintf(stderr, "Eroare la realocarea memoriei\n");
                exit(1);
            }
        spectacole = temp;

        spectacole[i].start_hour = x;
        spectacole[i].end_hour = y;
        i++;
        (*n)++;
    }

    spectacole = realloc(spectacole, (*n) * sizeof(Spectacol_t));
    return spectacole;
}

void print_data(Spectacol_t *spectacole, int n){
    for(int i = 0; i < n; i++){
        printf("%d - %d \n", spectacole[i].start_hour, spectacole[i].end_hour);
    }
}

int cmp_end_hour(const void *a, const void *b){
    Spectacol_t *p1 = (Spectacol_t *) a;
    Spectacol_t *p2 = (Spectacol_t *) b;

    if(p1->end_hour < p2->end_hour){
        return -1;
    }
    if(p1->end_hour > p2->end_hour){
        return 1;
    }

    return 0;
}

int alege_spectacole(Spectacol_t *spectacole, int n){
    int contor = 1;
    int index = 0;

    for(int i = 1; i < n; i ++){
        if(spectacole[i].start_hour >= spectacole[index].end_hour){
            index = i;
            contor++;
        }
    }
    return contor;
}