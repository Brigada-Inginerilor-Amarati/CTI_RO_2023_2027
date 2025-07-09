#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEBUG 0
#define ALPHABET_SIZE 26

typedef struct ArboreRegasire{
    int final_cuvant;
    struct ArboreRegasire *copii[ALPHABET_SIZE];
}ArboreRegasire_T;

ArboreRegasire_T *creazaNod(){
    ArboreRegasire_T *nod =  (ArboreRegasire_T*) malloc(sizeof(ArboreRegasire_T));

    if(nod == NULL){
        perror("Eroare la alocarea memoriei pentru nod.\n");
        return NULL;
    }

    nod->final_cuvant = 0;

    for(int i = 0; i < ALPHABET_SIZE; i++){
        nod->copii[i] = NULL;
    }

    return nod;
}

/*
* @brief Adauga un cuvant in arborele de regasire.
* @param radacina Pointer la radacina arborelui de regasire.
* @param cuvant Cuvantul de adaugat in arbore.
*/

void adaugaCuvant(ArboreRegasire_T* radacina, const char *cuvant){
    ArboreRegasire_T *nod_curent = radacina;

    // Parcurgem fiecare caracter din cuvant
    for(int i = 0; cuvant[i]; i++){
        // calculam indexul in functie de caracter
        int index = cuvant[i] - 'a';

        if(index < 0 || index >= ALPHABET_SIZE){
            fprintf(stderr, "Caracter invalid: %c in cuvantul %s\n", cuvant[i], cuvant);
            return;
        }

        // Daca nodul copil nu exista, il cream
        if(nod_curent->copii[index] == NULL){
            nod_curent->copii[index] = creazaNod();
        }

        // Mergem la nodul copil
        nod_curent = nod_curent->copii[index];
    }

    // Marcam nodul curent ca fiind final de cuvant
    nod_curent->final_cuvant = 1;
}

void elibereazaArbore(ArboreRegasire_T *radacina){
    if(radacina == NULL) return;

    // Eliberam recursiv toti copiii
    for(int i = 0; i < ALPHABET_SIZE; i++){
        elibereazaArbore(radacina->copii[i]);
    }

    // Eliberam nodul curent
    free(radacina);
}

void dfsPrint(ArboreRegasire_T* radacina, char *buffer, int nivel){
    if(radacina == NULL){
        return;
    }

    if(radacina->final_cuvant == 1){
        buffer[nivel] = '\0'; // Terminam stringul
        printf("%s\n", buffer); // Afisam cuvantul
    }

    for(int i = 0; i < ALPHABET_SIZE; i++){
        // verificam daca avem litere in noua lista
        if(radacina->copii[i] != NULL){
            // Adaugam litera curenta in buffer
            buffer[nivel] = 'a' + i; // Convertim indexul inapoi la caracter
            // Apelam recursiv pentru copilul curent
            dfsPrint(radacina->copii[i], buffer, nivel + 1);
        }
    }
}

/**
 * @brief calculeaza lungimea medie a cuvintelor din arbore
*/

void lungimeMedieCuvinte(ArboreRegasire_T *radacina, int nivel, int *numar_cuvinte, int *lungime_totala){
    if(radacina->final_cuvant == 1){
        *numar_cuvinte = *numar_cuvinte + 1;
        *lungime_totala = *lungime_totala + nivel;
    }   

    for(int i = 0; i < ALPHABET_SIZE; i++){
        if(radacina->copii[i] != NULL){
            lungimeMedieCuvinte(radacina->copii[i], nivel + 1, numar_cuvinte, lungime_totala);
        }
    }
}

/**
 * @brief o functie care calculeaza inaltimea arborelui
*/

int inaltimeMAX = 0;

void inaltimeArbore(ArboreRegasire_T *radacina, int nivel, int *pas){
    if(radacina == NULL){
        return;
    }

    if(radacina->final_cuvant == 1){
        if(nivel > inaltimeMAX){
            inaltimeMAX = nivel;
        }
    }

    for(int i = 0; i < ALPHABET_SIZE; i++){
        if(radacina->copii[i] != NULL){
            inaltimeArbore(radacina->copii[i], nivel + 1, pas);
        }
    }

    if(nivel > *pas){
        *pas = nivel;
    }

    if(DEBUG){
        printf("Nivelul curent: %d, Inaltime maxima: %d\n", nivel, inaltimeMAX);
    }
}

/**
 * @brief o functie care calculeaza nr de pagini din arbore
 */

int nrPagini(ArboreRegasire_T *radacina){
    if(radacina == NULL) return 0;

    int pagini = 1; // Contorizeaza pagina curenta

    for(int i = 0; i < ALPHABET_SIZE; i++){
        if(radacina->copii[i] != NULL){
            pagini += nrPagini(radacina->copii[i]);
        }
    }

    return pagini;
}

/**
 * @brief functie care afiseaza cel mai mare cuvant in ordine lexicografica
*/

char *celMaiMareCuvant = NULL;

void gasesteCelMaiMareCuvant(ArboreRegasire_T *radacina, char *buffer, int nivel){
    if(radacina->final_cuvant == 1){
        buffer[nivel] = '\0'; // Terminam stringul
        celMaiMareCuvant = strdup(buffer); // Copiem cuvantul gasit
        if(DEBUG){
            printf("Cuvant gasit: %s\n", celMaiMareCuvant);
        }
    }

    for(int i = ALPHABET_SIZE - 1; i >= 0; i--){
        if(radacina->copii[i] != NULL){
            buffer[nivel] = 'a' + i;
            gasesteCelMaiMareCuvant(radacina->copii[i], buffer, nivel + 1);
            break;
        }
    }
}

void gasesteUltimCuvant(ArboreRegasire_T*radacina, char *buffer, int nivel, char *ultimCuvant){
    if(radacina->final_cuvant == 1){
        buffer[nivel] = '\0'; // Terminam stringul
        strcpy(ultimCuvant, buffer); // Copiem cuvantul gasit
        if(DEBUG){
            printf("Ultimul cuvant gasit: %s\n", ultimCuvant);
        }
    }

    for(int i = 0; i < ALPHABET_SIZE; i++){
        if(radacina->copii[i] != NULL){
            buffer[nivel] = 'a' + i;
            gasesteUltimCuvant(radacina->copii[i], buffer, nivel + 1, ultimCuvant);
        }
    }
}

/**
 * @brief functie care gaseste cel mai scurt cuvant
 */

void gasesteCelMaiScurtCuvant(ArboreRegasire_T *radacina, char *buffer, int nivel, int *lungimeMinima, char *celMaiScurtCuvant){
    if(radacina->final_cuvant == 1){
        buffer[nivel] = '\0';

        if(strlen(buffer) < *lungimeMinima){
            *lungimeMinima =  strlen(buffer);
            strcpy(celMaiScurtCuvant, buffer);
            if(DEBUG){
                printf("Cuvant scurt gasit: %s\n", celMaiScurtCuvant);
            }   
        }
    }


    for(int i = 0; i < ALPHABET_SIZE; i++){
        if(radacina->copii[i] != NULL){
            buffer[nivel] = 'a' + i;
            gasesteCelMaiScurtCuvant(radacina->copii[i], buffer, nivel + 1, lungimeMinima, celMaiScurtCuvant);
        }
    }
}

void gasesteCelMaiLungCuvant(ArboreRegasire_T *radacina, char*buffer, int nivel, int *lungimeMaxima, char *celMaiLungCuvant){
    if(radacina->final_cuvant == 1){
        buffer[nivel] = '\0';

        if(strlen(buffer) > *lungimeMaxima){
            *lungimeMaxima = strlen(buffer);
            strcpy(celMaiLungCuvant, buffer);
            if(DEBUG){
                printf("Cuvant lung gasit: %s\n", celMaiLungCuvant);
            }   
        }
    }


    for(int i = 0; i < ALPHABET_SIZE; i++){
        if(radacina->copii[i] != NULL){
            buffer[nivel] = 'a' + i;

            gasesteCelMaiLungCuvant(radacina->copii[i], buffer, nivel + 1, lungimeMaxima, celMaiLungCuvant);
        }
    }
}

/**
 * @brief functie care afla primul cuvant din arbore
*/

void gasestePrimulCuvant(ArboreRegasire_T *radacina, char *buffer, int nivel, char *primulCuvant){
    if(radacina->final_cuvant == 1){
        buffer[nivel] = '\0';
        strcpy(primulCuvant, buffer);
        return;
    }

    for(int i = 0; i < ALPHABET_SIZE; i++){
        if(radacina->copii[i] != NULL){
            buffer[nivel] = 'a' + i;
            gasestePrimulCuvant(radacina->copii[i], buffer, nivel + 1, primulCuvant);
            if(strlen(primulCuvant) > 0){
                return; // Daca am gasit deja primul cuvant, iesim
            }
        }
    }
}

/**
 * @brief functie care gaseste cuvintele care au a doua litera un caracter dat
 */

void gasesteCuvantCuADouaLitera(ArboreRegasire_T *radacina, char *buffer, int nivel, char litera){
    if(radacina->final_cuvant == 1 && nivel >=1 && buffer[1] == litera){
        buffer[nivel] = '\0'; // Terminam stringul
        printf("%s\n", buffer); // Afisam cuvantul
    }

    for(int i = 0; i < ALPHABET_SIZE; i++){
        if(radacina->copii[i] != NULL){
            buffer[nivel] = 'a' + i; // Adaugam litera curenta in buffer
            gasesteCuvantCuADouaLitera(radacina->copii[i], buffer, nivel + 1, litera);
        }
    }
}


int main(int argc, char **argv){
    if(argc != 2){
        perror("Utilizare: ./p <fisier_intrare>\n");
        return 1;
    }

    FILE *fisier = fopen(argv[1], "r");
    if(fisier == NULL){
        perror("Eroare la deschiderea fisierului.\n");
        return 1;
    }

    ArboreRegasire_T *radacina = creazaNod();

    if(radacina == NULL){
        fclose(fisier);
        return 1;
    }

    char cuvant[100];

    while(fscanf(fisier, "%s", cuvant) == 1){
        // Convertim cuvantul la litere mici
        for(int i = 0; cuvant[i]; i++){
            cuvant[i] = tolower(cuvant[i]);
        }

        adaugaCuvant(radacina, cuvant);
    }

    fclose(fisier);

    char buffer[100];
    printf("Cuvintele din arborele de regasire sunt:\n");
    dfsPrint(radacina, buffer, 0);


    int numar_cuvinte = 0;
    int lungime_totala = 0;

    lungimeMedieCuvinte(radacina, 0, &numar_cuvinte, &lungime_totala);

    if(numar_cuvinte > 0){
        double lungime_medie = (double)lungime_totala / numar_cuvinte;
        printf("Lungimea medie a cuvintelor este: %.2f\n", lungime_medie);
    } else {
        printf("Nu exista cuvinte in arbore.\n");
    }

    int pas = 0;
    inaltimeArbore(radacina, 0, &pas);
    printf("Inaltimea maxima a arborelui este: %d\n", inaltimeMAX + 1);

    printf("Numarul de pagini din arbore este: %d\n", nrPagini(radacina));

    char buffer_cel_mai_mare[100];
    gasesteCelMaiMareCuvant(radacina, buffer_cel_mai_mare, 0);
    if(celMaiMareCuvant != NULL){
        printf("Cel mai mare cuvant in ordine lexicografica este: %s\n", celMaiMareCuvant);
        free(celMaiMareCuvant);
    } else {
        printf("Nu s-a gasit niciun cuvant in arbore.\n");
    }

    char ultimCuvant[100] = "";
    gasesteUltimCuvant(radacina, buffer, 0, ultimCuvant);
    if(strlen(ultimCuvant) > 0){
        printf("Ultimul cuvant in ordine lexicografica este: %s\n", ultimCuvant);
    } else {
        printf("Nu s-a gasit niciun cuvant in arbore.\n");
    }

    char buffer_cel_mai_scurt[100];
    int lungimeMinima = 100; // Initializam cu o valoare mare
    char celMaiScurtCuvant[100] = "";
    gasesteCelMaiScurtCuvant(radacina, buffer_cel_mai_scurt, 0, &lungimeMinima, celMaiScurtCuvant);
    if(lungimeMinima < 100){
        printf("Cel mai scurt cuvant este: %s\n", celMaiScurtCuvant);
    } else {
        printf("Nu s-a gasit niciun cuvant in arbore.\n");
    }

    char buffer_cel_mai_lung[100];
    int lungimeMaxima = 0; // Initializam cu 0
    char celMaiLungCuvant[100] = "";
    gasesteCelMaiLungCuvant(radacina, buffer_cel_mai_lung, 0, &lungimeMaxima, celMaiLungCuvant);
    if(lungimeMaxima > 0){
        printf("Cel mai lung cuvant este: %s\n", celMaiLungCuvant);
    } else {
        printf("Nu s-a gasit niciun cuvant in arbore.\n");
    }

    char primulCuvant[100] = "";
    gasestePrimulCuvant(radacina, buffer, 0, primulCuvant);
    if(strlen(primulCuvant) > 0){
        printf("Primul cuvant in ordine lexicografica este: %s\n", primulCuvant);
    } else {
        printf("Nu s-a gasit niciun cuvant in arbore.\n");
    }

    char litera;
    printf("Introduceti litera pentru a gasi cuvintele care au aceasta litera ca a doua: ");
    scanf(" %c", &litera);
    litera = tolower(litera); // Convertim la litera mica
    printf("Cuvintele care au '%c' ca a doua litera sunt:\n", litera);
    gasesteCuvantCuADouaLitera(radacina, buffer, 0, litera);        



    elibereazaArbore(radacina);
    if(DEBUG){
        printf("Arborele de regasire a fost eliberat.\n");
    }

    return 0;
}