#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 50

// optiuni pt citire
#define MATRICE_ADIACENTA 1


typedef struct Graf {
	int nr_of_nodes;
	int matrice_adiacenta[MAX_NODES + 1][MAX_NODES + 1];
}Graf_t;

typedef struct Queue {
	int data[MAX_NODES];
	int front;
	int rear;
}Queue_t;

typedef struct Stack {
	int data[MAX_NODES];
	int top;
}Stack_t;

void initQueue(Queue_t* coada) {
	coada->front = -1;
	coada->rear = -1;
	memset(coada->data, 0, sizeof(coada->data));
}

int isQueueEmpty(Queue_t* coada) {
	return coada->front == -1;
}

int isQueueFull(Queue_t* coada) {
	return coada->rear >= MAX_NODES - 1;
}

void enqueue(Queue_t* coada, int elementAdaugat) {
	if (isQueueFull(coada)) {
		printf("Coada este plina\n");
		return;
	}

	if (isQueueEmpty(coada)) {
		coada->front = 0;
		coada->rear = -1;
	}

	coada->rear++;

	coada->data[coada->rear] = elementAdaugat;
}

int dequeue(Queue_t* coada) {
	if (isQueueEmpty(coada)) {
		printf("coada este goala \n");
		return;
	}

	int valueRemoved = coada->data[coada->front];

	if (coada->front == coada->rear) {
		coada->front = -1;
		coada->rear = -1;
	}
	else {
		for (int i = 0; i < coada->rear; i++) {
			coada->data[i] = coada->data[i + 1];
		}
		coada->rear--;
	}

	return valueRemoved;
}

void initStack(Stack_t* stiva) {
	stiva->top = -1;
	memset(stiva->data, 0, sizeof(stiva->data));
}

int isStackEmpty(Stack_t* stiva) {
	return stiva->top == -1;
}

int isStackFull(Stack_t* stiva) {
	return stiva->top >= MAX_NODES;
}

void push(Stack_t* stiva, int elementAdaugat) {
	if (isStackFull(stiva)) {
		printf("Stiva este plina \n");
		return;
	}

	if (isStackEmpty(stiva)) {
		stiva->top = -1;
	}

	stiva->top++;

	stiva->data[stiva->top] = elementAdaugat;
}

int pop(Stack_t* stiva) {
	if (isStackEmpty(stiva)) {
		printf("Stiva este goala\n");
		return;
	}

	int poppedValue = stiva->data[stiva->top];
	stiva->top--;

	return poppedValue;
}

void citesteGraf_matriceAdiacenta(Graf_t* graf, FILE* fin) {
	// citim nr de noduri
	fscanf(fin, "%d", &graf->nr_of_nodes);

	if (graf->nr_of_nodes >= MAX_NODES) {
		perror("Nr de noduri depaseste capacitatea maxima\n");
		return;
	}

	// citim matricea de adiacenta
	/*
			1 2 3 
		1
		2
		3
	*/

	for (int i = 1; i <= graf->nr_of_nodes; i++) {
		for (int j = 1; j <= graf->nr_of_nodes; j++) {
			fscanf(fin, "%d", &graf->matrice_adiacenta[i][j]);
		}
	}
}

void citesteGraf_Muchii(Graf_t* graf, FILE* fin) {
	fscanf(fin, "%d", &graf->nr_of_nodes);

	if (graf->nr_of_nodes >= MAX_NODES) {
		perror("Nr de noduri depaseste capacitatea maxima\n");
		return;
	}

	int node1, node2;

	while (fscanf(fin, "%d %d", &node1, &node2) == 2) {
		graf->matrice_adiacenta[node1][node2] = 1;
		graf->matrice_adiacenta[node2][node1] = 1;
	}
}

void afiseazaMatriceAdiacenta(Graf_t *graf) {
	for (int i = 1; i <= graf->nr_of_nodes; i++) {
		for (int j = 1; j <= graf->nr_of_nodes; j++) {
			printf("%d ", graf->matrice_adiacenta[i][j]);
		}
		printf("\n");
	}
}

// bfs

void bfs(Graf_t graf, int nod_start) {
	// noduri vizitate
	unsigned vizitat[MAX_NODES] = { 0 };

	Queue_t coada;
	initQueue(&coada);

	// incarcam nodul de start
	enqueue(&coada, nod_start);
	// marcam de asemenea nodul ca vizitat
	vizitat[nod_start] = 1;

	// incepem sa scoadem din coada -> si sa vizitam vecinii fiecarui nod
	while (!isQueueEmpty(&coada)) {
		int nodCurent = dequeue(&coada);
		printf("%d ", nodCurent);

		// parcurgem in ordine toti vecinii acestui nod pe care l-am tras din coada
		for (int i = 1; i <= graf.nr_of_nodes; i++) {
			// verificam daca avem vecin nevizitat deja
			if (graf.matrice_adiacenta[nodCurent][i] == 1 && vizitat[i] == 0) {
				// in cazul in care gasim, il bagam in coada si il marcam ca si vizitat
				enqueue(&coada, i);
				//printf("Adaugam nodul %d in coada\n", i);
				vizitat[i] = 1;
			}
		}
	}
}

// shortest path

void shortest_path(Graf_t graf, int nod_start, int nod_final) {
	// noduri vizitate
	unsigned vizitat[MAX_NODES] = { 0 };

	// vector cu noduri -> parinte
	int parinte[MAX_NODES];

	Queue_t coada;
	initQueue(&coada);

	// incarcam nodul de start
	enqueue(&coada, nod_start);
	// marcam de asemenea nodul ca vizitat
	vizitat[nod_start] = 1;
	// aici vom pune -1 in vectorul parinte
	parinte[nod_start] = -1;

	// incepem sa scoadem din coada -> si sa vizitam vecinii fiecarui nod
	while (!isQueueEmpty(&coada)) {
		int nodCurent = dequeue(&coada);

		// daca ajungem la destinatie ne oprim
		if (nodCurent == nod_final) {
			break;
		}

		// parcurgem in ordine toti vecinii acestui nod pe care l-am tras din coada
		for (int i = 1; i <= graf.nr_of_nodes; i++) {
			// verificam daca avem vecin nevizitat deja
			if (graf.matrice_adiacenta[nodCurent][i] == 1 && vizitat[i] == 0) {
				// in cazul in care gasim, il bagam in coada si il marcam ca si vizitat
				enqueue(&coada, i);
				//printf("Adaugam nodul %d in coada\n", i);
				vizitat[i] = 1;
				parinte[i] = nodCurent; // marcam parintele fiecarui nod parcurs -> ca sa stim de cn se leaga
			}
		}
	}

	if (!vizitat[nod_final]) {
		printf("Nu putem gasi drum de la %d la %d\n", nod_start, nod_final);
		return;
	}

	// refacem drumul parcurs
	int path[MAX_NODES];
	int index = 0;
	
	for (int i = nod_final; i != -1; i = parinte[i]) {
		path[index++] = i;
	}

	printf("Drumul de la %d la %d : ", nod_start, nod_final);
	for (int i = (index - 1); i >= 0; i--) {
		printf("%d ", path[i]);
	}

	printf("\n");
}

// dfs

// pe datele noastre -> 1 2 3 4 5
void dfs(Graf_t graf, int nod_start) {
	unsigned vizitat[MAX_NODES] = { 0 };

	Stack_t stack;
	initStack(&stack);

	push(&stack, nod_start);
	//

	while (!isStackEmpty(&stack)) {
		int nodCurent = pop(&stack);

		// sarim nodul deja vizitat
		if (vizitat[nodCurent] == 1) {//
			continue;//
		}//

		printf("%d ", nodCurent);
		vizitat[nodCurent] = 1;//

		for (int i = graf.nr_of_nodes; i > 0; i--) {
			if (graf.matrice_adiacenta[nodCurent][i] == 1 && vizitat[i] == 0) {
				push(&stack, i);
				//
			}
		}
	}

}

// componente conexe

void bfsComponent(Graf_t graf, unsigned* vizitat, int nodStart, int numarComponente) {
	Queue_t coada;
	initQueue(&coada);

	enqueue(&coada, nodStart);
	vizitat[nodStart] = 1;

	printf("Componenta %d : %d ", numarComponente, nodStart);

	while (!isQueueEmpty(&coada)) {
		int nodCurent = dequeue(&coada);

		for (int i = 1; i <= graf.nr_of_nodes; i++) {
			if (graf.matrice_adiacenta[nodCurent][i] == 1 && vizitat[i] == 0) {
				enqueue(&coada, i);
				vizitat[i] = 1;

				printf("%d ", i);
			}
		}
	}
}

int numaraComponenteConexe(Graf_t graf) {
	unsigned vizitat[MAX_NODES] = { 0 };
	int numar_componente = 0;

	for (int i = 1; i <= graf.nr_of_nodes; i++) {
		if (vizitat[i] == 0) {
			numar_componente++;
			bfsComponent(graf, vizitat, i, numar_componente);
		}
	}
	
	return numar_componente;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		perror("Incorrect ussage: ./program filename");
		return 1;
	}

	FILE* fin = fopen(argv[1], "r");

	if (fin == NULL) {
		perror("Eroare deschidere fisier\n");
		return 2;
	}
	
	Graf_t graf;

	graf.nr_of_nodes = 0;
	memset(graf.matrice_adiacenta, 0, sizeof(graf.matrice_adiacenta));

	if (MATRICE_ADIACENTA) {
		citesteGraf_matriceAdiacenta(&graf, fin);
	}
	else {
		citesteGraf_Muchii(&graf, fin);
	}

	// data.txt
	// vom cauta de la 1 la 5
	// a legat de b, c, d
	// b legat de a
	// c legat de a, d, e
	// d legat de a, c, e
	// e legat de c, d
	int start_node = 0;
	int end_node = 0;

	fscanf(fin, "%d %d", &start_node, &end_node);

	fclose(fin);

	printf("------------------------------------------\n");
	printf("Matrice adiacenta :\n");
	afiseazaMatriceAdiacenta(&graf);
	printf("------------------------------------------\n");

	printf("------------------------------------------\n");
	printf("Parcurgere cu BFS:\n");
	bfs(graf, 1);
	printf("\n");
	printf("------------------------------------------\n");

	printf("------------------------------------------\n");
	shortest_path(graf, start_node, end_node);
	printf("------------------------------------------\n");

	printf("------------------------------------------\n");
	printf("Parcurgere cu DFS:\n");
	dfs(graf, 1);
	printf("\n");
	printf("------------------------------------------\n");

	printf("------------------------------------------\n");
	int numarComponenteConexe = numaraComponenteConexe(graf);
	printf("\nDeci, nr de componente conexe este : %d\n", numarComponenteConexe);
	printf("------------------------------------------\n");

	return 0;
}