#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


// -----------------
// Defines
// -----------------

#define MAX_NODES 50

#define ENABLE_DEBUG 1

// -----------------
// Data Structures
// -----------------

// ----------------
// Graf 
// -------------------

typedef struct Graf {
	int numberOfNodes;
	int adjacencyMatrix[MAX_NODES][MAX_NODES];
}Graf_T;

// -----------------
// Functions
// -----------------

// ----------------------
// Graf Functions
// ----------------------

void initGraf(Graf_T* graf) {
	memset(graf, 0, sizeof(Graf_T));
}

void readFromFile(Graf_T* graf, FILE* fin) {
	int i, j;

	for (i = 0; i < graf->numberOfNodes; i++) {
		for (j = 0; j < graf->numberOfNodes; j++) {
			if (fscanf(fin, "%d", &graf->adjacencyMatrix[i][j]) != 1) {
				perror("Error reading adjacency matrix from file");
				exit(EXIT_FAILURE);
			}
		}
	}
}

void printGraf(const Graf_T* graf) {
	int i, j;
	printf("Number of Nodes: %d\n", graf->numberOfNodes);
	printf("Adjacency Matrix:\n");
	for (i = 0; i < graf->numberOfNodes; i++) {
		for (j = 0; j < graf->numberOfNodes; j++) {
			printf("%d ", graf->adjacencyMatrix[i][j]);
		}
		printf("\n");
	}
}


// DIFFERENT FUNCTIONS

// function to veify if a graph is orientated or not
int isOrientated(const Graf_T* graf) {
	for (int i = 0; i < graf->numberOfNodes; i++) {
		for (int j = 0; j < graf->numberOfNodes; j++) {
			if (graf->adjacencyMatrix[i][j] != graf->adjacencyMatrix[j][i]) {
				return 1; // Graph is orientated
			}
		}
	}
	return 0; // Graph is not orientated
}

// ALGORITHMS

void dijkstra(Graf_T* graf, int startNode) {
	// we ll use this array to mark the visited nodes
	int visited[MAX_NODES] = { 0 };

	// this array will be used in order to store the minimum cost to reach each node
	int costArray[MAX_NODES] = { 0 };

	// this array we ll use to store the previous node in the path
	int previousNode[MAX_NODES] = { 0 };

	for (int i = 0; i < graf->numberOfNodes; i++) {
		costArray[i] = INT_MAX; // Initialize all costs to infinity
		previousNode[i] = -1;   // Initialize previous nodes to -1
	}

	// Cost to reach the start node is 0
	costArray[startNode] = 0;
	visited[startNode] = 1; // Mark the start node as visited

	int currentNode = startNode;

	// this for loop will iterate through all the nodes in the graph
	for (int pas = 0; pas < graf->numberOfNodes - 1; pas++) {
		int minCost = INT_MAX;

		// go through all the nodes to find the node with the minimum cost
		for (int i = 0; i < graf->numberOfNodes; i++) {
			if (!visited[i] && graf->adjacencyMatrix[currentNode][i] > 0) {
				if (costArray[i] > (costArray[currentNode] + graf->adjacencyMatrix[currentNode][i])) {
					costArray[i] = costArray[currentNode] + graf->adjacencyMatrix[currentNode][i];
					previousNode[i] = currentNode;
				}
			}
		}

		// Find the next node with the minimum cost
		for (int i = 0; i < graf->numberOfNodes; i++) {
			if (!visited[i] && costArray[i] < minCost) {
				minCost = costArray[i];
				currentNode = i;
			}
		}

		// Mark the current node as visited
		visited[currentNode] = 1;
	}

	// Print the results
	printf("Dijkstra's Algorithm Results:\n");

	printf("Node\tCost\tPrevious Node\n");

	for (int i = 0; i < graf->numberOfNodes; i++) {
		if (costArray[i] == INT_MAX) {
			printf("%d\tINF\t-\n", i);
		}
		else {
			printf("%d\t%d\t%d\n", i, costArray[i], previousNode[i]);
		}
	}

	printf("\nShortest paths from node %d:\n", startNode);

	for (int i = 0; i < graf->numberOfNodes; i++) {
		if (i == startNode)
			continue; // Skip the start node itself

		printf("Path to node %d: ", i);

		// reconstruct the path from the start node to node i
		int path[MAX_NODES];
		int pathIndex = 0;

		// Backtrack to find the path
		for (int j = i; j != -1; j = previousNode[j]) {
			path[pathIndex++] = j;
		}

		// Print the path in reverse order
		for (int j = pathIndex - 1; j >= 0; j--) {
			printf("%d ", path[j]);

			if (j > 0) {
				printf(" -> ");
			}
		}
		printf("\n");
	}

	printf("\n");
}
int T[MAX_NODES][MAX_NODES];	//	matrice traseu

void floyd(Graf_T graf) {
	// basically, this array is the adjacency matrix of the graph modified
	int D[MAX_NODES][MAX_NODES];	//	matrice cost

	for (int i = 0; i < graf.numberOfNodes; i++)	//	initializare matrici
		for (int j = 0; j < graf.numberOfNodes; j++) {
			if (i == j)
				D[i][j] = 0;
			else if (graf.adjacencyMatrix[i][j] == 0)
				D[i][j] = INT_MAX;
			else
				D[i][j] = graf.adjacencyMatrix[i][j];

			T[i][j] = -1;
		}


	for (int k = 0; k < graf.numberOfNodes; k++)	//	alg in sine
		for (int i = 0; i < graf.numberOfNodes; i++)
			for (int j = 0; j < graf.numberOfNodes; j++)
				if (D[i][k] != INT_MAX && D[k][j] != INT_MAX)
					if (D[i][j] > D[i][k] + D[k][j]) {
						D[i][j] = D[i][k] + D[k][j];
						T[i][j] = k;
					}

	for (int i = 0; i < graf.numberOfNodes; i++) {	//	afisare matrice floyd
		for (int j = 0; j < graf.numberOfNodes; j++)
			if (D[i][j] == INT_MAX)
				printf("INF ");
			else
				printf("%d ", D[i][j]);

		putchar('\n');
	}

	for (int i = 0; i < graf.numberOfNodes; i++) {	//	afisare matrice traseu
		for (int j = 0; j < graf.numberOfNodes; j++)
			printf("%d ", T[i][j]);
		putchar('\n');
	}
}

void traseu(int i, int j) {
	int k = T[i][j];
	if (k != -1) {
		traseu(i, k);
		printf("%d ", k);
		traseu(k, j);
	}
}

void warshal(Graf_T graf) {
	int W[MAX_NODES][MAX_NODES];

	// 1 means there is a path, 0 means no path

	for (int i = 0; i < graf.numberOfNodes; i++)
		for (int j = 0; j < graf.numberOfNodes; j++)
			W[i][j] = (graf.adjacencyMatrix[i][j] != 0 ? 1 : 0);

	for (int k = 0; k < graf.numberOfNodes; k++)
		for (int i = 0; i < graf.numberOfNodes; i++)
			for (int j = 0; j < graf.numberOfNodes; j++)
				if (!W[i][j])
					W[i][j] = W[i][k] && W[k][j];

	for (int i = 0; i < graf.numberOfNodes; i++) {	//	afisare matrice
		for (int j = 0; j < graf.numberOfNodes; j++)
			printf("%d ", W[i][j]);
		putchar('\n');
	}
}

// ----------------------
// MAIN
// ----------------------

int main(int argc, char** argv) {
	if (argc != 2) {
		perror("Usage: ./main <filename>");
		return 1;
	}

	FILE* fin = fopen(argv[1], "r");

	if (!fin) {
		perror("Error opening file");
		return 1;
	}

	Graf_T graf;
	initGraf(&graf);

	if (fscanf(fin, "%d", &graf.numberOfNodes) != 1) {
		perror("Error reading number of nodes from file");
		fclose(fin);
		return 1;
	}

	if (graf.numberOfNodes <= 0 || graf.numberOfNodes > MAX_NODES) {
		perror("Invalid number of nodes");
		fclose(fin);
		return 1;
	}

	readFromFile(&graf, fin);

	fclose(fin);

	if (ENABLE_DEBUG) {
		printf("-------------------------------\n");
		printGraf(&graf);
		printf("-------------------------------\n");
	}

	printf("--------------------------------\n");
	printf("Running Dijkstra's algorithm from node 0:\n");
	dijkstra(&graf, 0);
	printf("--------------------------------\n");

	int src = 0;
	int dst = 4;
	printf("--------------------------------\n");
	printf("Running Floyd's algorithm\n");
	floyd(graf);
	printf("--------------------------------\n");


	printf("traseu %d -> %d\n", src, dst);
	printf("%d ", src);
	traseu(src, dst);
	printf("%d\n", dst);

	printf("--------------------------------\n");
	printf("Running Warshal's algorithm\n");
	warshal(graf);
	printf("--------------------------------\n");

	return 0;
}	