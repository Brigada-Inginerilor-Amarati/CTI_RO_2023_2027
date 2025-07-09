#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// --------------------
// Defines
// --------------------
#define MAX_NODES 50

#define ENABLE_DEBUG 1

// --------------------
// Structures
// --------------------
typedef struct Graf {
	int adjancencyMatrix[MAX_NODES][MAX_NODES];
	int numNodes;
}Graf_T;

//typedef struct GrafChar {
//	int adjancencyMatrix[MAX_NODES][MAX_NODES];
//	char nodeNames[MAX_NODES];
//	int numNodes;
//}GrafChar_T;

// --------------------
// Functions
// --------------------

void initGraf(Graf_T* graf, int numNodes) {
	if (numNodes > MAX_NODES) {
		perror("Number of nodes exceeds maximum limit.\n");
		exit(1);
	}
	graf->numNodes = numNodes;
	
	memset(graf->adjancencyMatrix, 0, sizeof(graf->adjancencyMatrix));
}

// function to read the adjancency matrix from a file with weights
void readAdjancencyMatrix(FILE* fin, Graf_T* graf) {
	for (int i = 0; i < graf->numNodes; i++) {
		for (int j = 0; j < graf->numNodes; j++) {
			if (fscanf(fin, "%d", &graf->adjancencyMatrix[i][j]) != 1) {
				perror("Error reading adjancency matrix.\n");
				exit(3);
			}
		}
	}
}

void printAdjancencyMatrix(const Graf_T* graf) {
	for (int i = 0; i < graf->numNodes; i++) {
		for (int j = 0; j < graf->numNodes; j++) {
			printf("%d ", graf->adjancencyMatrix[i][j]);
		}
		printf("\n");
	}
}

// Prim algorithm to find the minimum spanning tree -> with while

void prim(Graf_T* graf) {
	int visited[MAX_NODES] = { 0 }; // Array to keep track of visited nodes
	int totalCost = 0; // Total cost of the minimum spanning tree

	visited[0] = 1; // Start from the first node
	int selectedEdges = 0; // Number of edges selected

	printf("Edges in the Minimum Spanning Tree:\n");

	while (selectedEdges < graf->numNodes - 1) {
		int min = INT_MAX;
		int u = -1; 
		int v = -1;

		for (int i = 0; i < graf->numNodes; i++) {
			if (visited[i] == 1) {

				for (int j = 0; j < graf->numNodes; j++) {
					if (visited[j] == 0 && graf->adjancencyMatrix[i][j] != 0 && graf->adjancencyMatrix[i][j] < min) {
						min = graf->adjancencyMatrix[i][j];
						u = i;
						v = j;
					}
				}
			}
		}

		if (u != -1 && v != -1) {
			printf("Edge: %d - %d, Weight: %d\n", u, v, graf->adjancencyMatrix[u][v]);
			totalCost += graf->adjancencyMatrix[u][v];
			visited[v] = 1; // Mark the new node as visited
			selectedEdges++;
		}
		else {
			perror("No more edges to select.\n");
			break;
		}
	}

	printf("Total cost of the Minimum Spanning Tree: %d\n", totalCost);
}

void primAlgorithm(Graf_T* graf) {
	int COSTMIN[MAX_NODES];
	int APROPIAT[MAX_NODES];
	int included[MAX_NODES] = { 0 }; // Echivalent cu mulțimea U
	int totalCost = 0;

	for (int i = 0; i < graf->numNodes; i++) {
		COSTMIN[i] = INT_MAX;
		APROPIAT[i] = -1;
	}
	COSTMIN[0] = 0;
	included[0] = 1; // 👈 MARCĂM explicit nodul 0 ca fiind în U

	// Inițializare pentru vecinii lui 0
	for (int i = 1; i < graf->numNodes; i++) {
		if (graf->adjancencyMatrix[0][i] != 0) {
			COSTMIN[i] = graf->adjancencyMatrix[0][i];
			APROPIAT[i] = 0;
		}
	}

	printf("Edges in the Minimum Spanning Tree (COSTMIN/APROPIAT):\n");

	for (int step = 0; step < graf->numNodes - 1; step++) {
		int min = INT_MAX, k = -1;

		// Găsim nodul k din N-U cu costul minim
		for (int i = 0; i < graf->numNodes; i++) {
			if (!included[i] && COSTMIN[i] < min) {
				min = COSTMIN[i];
				k = i;
			}
		}

		if (k == -1) {
			fprintf(stderr, "Error: Graph may be disconnected.\n");
			break;
		}

		included[k] = 1; // Adaugă k în U

		if (APROPIAT[k] != -1) {
			printf("Edge: %d - %d, Weight: %d\n", APROPIAT[k] + 1, k + 1, graf->adjancencyMatrix[k][APROPIAT[k]]);
			totalCost += graf->adjancencyMatrix[k][APROPIAT[k]];
		}

		// Actualizăm valorile pentru nodurile rămase
		for (int j = 0; j < graf->numNodes; j++) {
			int cost = graf->adjancencyMatrix[k][j];
			if (!included[j] && cost != 0 && cost < COSTMIN[j]) {
				COSTMIN[j] = cost;
				APROPIAT[j] = k;
			}
		}
	}

	printf("Total cost of the Minimum Spanning Tree: %d\n", totalCost);
}




// --------------------
// Main
// --------------------
int main(int argc, char** argv) {
	if (argc != 2) {
		perror("Incorrect ussage of arguments: ./p <filename>\n");
		return 1;
	}

	FILE* fin = fopen(argv[1], "r");

	if (fin == NULL) {
		perror("Error opening the file.\n");
		return 2;
	}

	Graf_T graf;

	int numNodes;

	if (fscanf(fin, "%d", &numNodes) != 1) {
		perror("Error reading number of nodes.\n");
		fclose(fin);
		return 3;
	}

	initGraf(&graf, numNodes);

	readAdjancencyMatrix(fin, &graf);

	if (ENABLE_DEBUG) {
		printf("-----------------------\nAdjancency Matrix:\n");
		printf("-----------------------\n");
		printAdjancencyMatrix(&graf);
		printf("-----------------------\n");
	}

	// Call the Prim's algorithm functions
	printf("------------------------\n");
	printf("Running Prim's algorithm with while loop:\n");
	prim(&graf);
	printf("------------------------\n");


	// Call the Prim's algorithm function with the second implementation
	printf("------------------------\n");
	printf("Running Prim's algorithm with for loop:\n");
	primAlgorithm(&graf);
	printf("------------------------\n");

	fclose(fin);
	return 0;
}