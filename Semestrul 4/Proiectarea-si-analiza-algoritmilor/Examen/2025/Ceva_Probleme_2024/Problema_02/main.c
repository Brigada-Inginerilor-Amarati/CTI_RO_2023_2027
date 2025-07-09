#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define DEBUG 0

#define MAX 20

typedef struct Graf {
	unsigned n;
	int matrice[MAX][MAX];
} Graf_t;

void print_graf(Graf_t graf) {
	for (unsigned i = 0; i < graf.n; i++) {
		for (unsigned j = 0; j < graf.n; j++)
			printf("%d ", graf.matrice[i][j]);
		putchar('\n');
	}
}

Graf_t primAlg(Graf_t* graf, int start_nod) {
	Graf_t ElectroCarp;
	ElectroCarp.n = graf->n;	//	acelasi numar de orase trebuie conectate

	for (unsigned i = 0; i < ElectroCarp.n; i++)	//	initializam, pentru ca putem avea junk in loc de 0 in muchiile pe care nu le vom actualiza
		for (unsigned j = 0; j < ElectroCarp.n; j++)
			ElectroCarp.matrice[i][j] = 0;

	int vizitat[MAX] = { 0 };

	int totalCost = 0;

	vizitat[start_nod] = 1;

	int index = 0;

	// noduri[index++] = start_nod;

	for (int i = 1; i < graf->n; i++) {
		int minCost = INT_MAX;
		int u = -1;
		int v = -1;

		// for pt multimea U, noduri vizitate
		for (int j = 0; j < graf->n; j++) {
			if (vizitat[j] == 1) {
				// for pt multimea V, noduri nevizitate
				for (int k = 0; k < graf->n; k++) {
					if (graf->matrice[j][k] != 0 && vizitat[k] == 0) {
						// gasim muchia cu costul minim
						if (graf->matrice[j][k] < minCost) {
							minCost = graf->matrice[j][k];
							u = j;
							v = k;
						}
					}
				}
			}
		}

		if (u != -1 && v != -1) {
			vizitat[v] = 1;
			ElectroCarp.matrice[u][v] = graf->matrice[u][v];	//	adaugam muchia gasita in ElectroCarp, costul ei
			ElectroCarp.matrice[v][u] = graf->matrice[u][v];
			totalCost += minCost;
			if (DEBUG) {
				printf("Adaugam muchia (%d, %d) cu costul %d\n", u, v, minCost);
			}
		}
		else {
			if (DEBUG) {
				printf("Nu mai exista muchii de adaugat.\n");
			}
			break;
		}
	}

	printf("Cost total al arborelui acoperitor: %d\n", totalCost);

	return ElectroCarp;
}

Graf_t power_grid(Graf_t Carpathia, Graf_t ElectroCarp, int limitareLinii, int start_nod) {
	//	o sa updatam Carpathia locala, pentru a dubla costurile pe muchiile care deja se afla in ElectroCarp
	for (unsigned i = 0; i < Carpathia.n; i++)	//	deoarece PowerGrid va avea cost duble pe ele si ne vom folosi de Carpathia noua pentru a forma PowerGrid
		for (unsigned j = 0; j < Carpathia.n; j++)	//	ea va fi harta de baza pentru PowerGrid, spre deosebire de ElectroCarp unde ne am folosit de originala Carpathia, neavand constrangeri
			if (Carpathia.matrice[i][j] != 0 && ElectroCarp.matrice[i][j] != 0)
				Carpathia.matrice[i][j] *= 2;

	printf("Carpathia relativa pentru PowerGrid:\n");
	print_graf(Carpathia);
	putchar('\n');

	//	avand restrictiile pe Carpathia noua, putem pur si simplu sa facem primAlg pe Carpathia noua pentru a afla arborele minim, care de data asta va fi repr de PowerGrid
	Graf_t PowerGrid;
    PowerGrid.n = Carpathia.n;	//	acelasi numar de orase trebuie conectate
    for (unsigned i = 0; i < PowerGrid.n; i++)	//	initializam, pentru ca putem avea junk in loc de 0 in muchiile pe care nu le vom actualiza
        for (unsigned j = 0; j < PowerGrid.n; j++)
            PowerGrid.matrice[i][j] = 0;
    
    int vizitat[MAX] = { 0 };

	int totalCost = 0;

	vizitat[start_nod] = 1;

	int index = 0;

    for (int i = 1; i < Carpathia.n; i++) {
		int minCost = INT_MAX;
		int u = -1;
		int v = -1;

		// for pt multimea U, noduri vizitate
		for (int j = 0; j < Carpathia.n; j++) {
			if (vizitat[j] == 1) {
				// for pt multimea V, noduri nevizitate
				for (int k = 0; k < Carpathia.n; k++) {
					if (Carpathia.matrice[j][k] != 0 && vizitat[k] == 0) {
						// gasim muchia cu costul minim
						if (Carpathia.matrice[j][k] < minCost) {
                            // verificare pentru limitare linii
                            if(limitareLinii == 0 && ElectroCarp.matrice[j][k] != 0) {
                                continue;	//	daca nu mai avem linii disponibile si muchia e deja in ElectroCarp, o ignoram
                            }
							minCost = Carpathia.matrice[j][k];
							u = j;
							v = k;
						}
					}
				}
			}
		}

		if (u != -1 && v != -1) {
			vizitat[v] = 1;
			PowerGrid.matrice[u][v] = Carpathia.matrice[u][v];	//	adaugam muchia gasita in ElectroCarp, costul ei
			PowerGrid.matrice[v][u] = Carpathia.matrice[u][v];
            // scadem limitarea doar daca muchia este in ElectroCarp
            if(ElectroCarp.matrice[u][v] != 0) {
                limitareLinii--;
            }
			totalCost += minCost;
			if (DEBUG) {
				printf("Adaugam muchia (%d, %d) cu costul %d\n", u, v, minCost);
			}
		}
		else {
			if (DEBUG) {
				printf("Nu mai exista muchii de adaugat.\n");
			}
			break;
		}
	}

	printf("Cost total al arborelui acoperitor: %d\n", totalCost);


	return PowerGrid;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("eroare argumente\n");
		return 1;
	}

	Graf_t Carpathia;	//	asta e reprezentarea intregii tari, cu costurile intre orase

	FILE* fis = fopen(argv[1], "r");

	fscanf(fis, "%u", &Carpathia.n);

	for (unsigned i = 0; i < Carpathia.n; i++)
		for (unsigned j = 0; j < Carpathia.n; j++)
			fscanf(fis, "%d", &Carpathia.matrice[i][j]);

	

	printf("Carpathia:\n");
	print_graf(Carpathia);
	putchar('\n');

	//	asta e reprezentarea liniilor de electricitate folosite de ElectroCarp care leaga toate orasele 
	Graf_t ElectroCarp = primAlg(&Carpathia, 0);	//	din enunt ne dam seamna ca se refera la arborele de acoperire minim, arborele de acoperire minim e defapt un graf conex aciclic, deci facem Prim aflam arborele si il reprezentam prin graful asta ElectrCarp

	printf("ElectroCarp:\n");
	print_graf(ElectroCarp);
	putchar('\n');

    int limitareLinii = 0;
    fscanf(fis, "%d", &limitareLinii);	//	asta e numarul de linii de electricitate pe care ElectroCarp le poate folosi, deci trebuie sa ne asiguram ca nu depasim acest numar in PowerGrid
    fclose(fis);
	//	trebuie sa conecteze toate orasele, daca foloseste muchii deja existente in ElectroCarp, costul lor pentru PowerGrid se dubleaza
	Graf_t PowerGrid = power_grid(Carpathia, ElectroCarp, limitareLinii, 0);	//	iar trebuie sa avem cel putin doua rute intre orase, o bucla loop ciclu de am lucrat ieri

    printf("PowerGrid:\n");
    print_graf(PowerGrid);
    putchar('\n');


	return 0;
}