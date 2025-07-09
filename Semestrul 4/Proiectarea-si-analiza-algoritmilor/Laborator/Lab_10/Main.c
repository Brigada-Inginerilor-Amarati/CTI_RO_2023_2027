#include <stdio.h>
#include <stdlib.h>

// ====================================
// Defines
// ====================================

#define MAX_NODES 50

// ====================================
// Data Structures
// ====================================

// ---------------------------------
// data strucuture for a queue
// ---------------------------------

typedef struct Queue {
	int data[MAX_NODES];
	int front;
	int rear;
}Queue_t;

// ---------------------------------
// data structure for a stack
// ---------------------------------

typedef struct Stack {
	int data[MAX_NODES];
	int top;
}Stack_t;

// --------------------------------
// data structure for the graph -> nr of nodes and adjacency list
// --------------------------------

typedef struct Graph {
	unsigned nr_of_nodes;
	unsigned adjacency_matrix[MAX_NODES][MAX_NODES];
}Graph_t;

// =====================================
// Function 
// =====================================

// ===================================
// Queue functions
// ===================================

// (1) Initialize the queue

void initQueue(Queue_t* queue) {
	queue->front = -1;
	queue->rear = -1;
	memset(queue->data, 0, sizeof(queue->data));
}

// (2) Check if the queue is empty

int isQueueEmpty(Queue_t* queue) {
	return queue->front == -1;
}

// (3) Check if the queue is full

int isQueueFull(Queue_t* queue) {
	return queue->rear == MAX_NODES - 1;
}

// (4) Enqueue an element

void enqueue(Queue_t* queue, int valueAdded) {
	// check if there is space in the queue
	if(isQueueFull(queue)){
		perror("Queue is full");
		return;
	}

	// check if the queue is empty
	if (isQueueEmpty(queue)) {
		// set the front to 0 in order to add the first element
		queue->front = 0;
	}

	// add the element to the queue
	queue->rear++;

	queue->data[queue->rear] = valueAdded;
}

// (5) Dequeue an element

int dequeue(Queue_t* queue) {
	// check if the queue is empty
	if (isQueueEmpty(queue)) {
		perror("Queue is empty");
		return -1;
	}

	// get the element from the front of the queue
	int valueRemoved = queue->data[queue->front];

	// check if the queue has only one element
	if (queue->front == queue->rear) {
		// reset the queue
		queue->front = -1;
		queue->rear = -1;
	}
	else {
		// move the front to the next element
		for (int i = 0; i < queue->rear; i++) {
			queue->data[i] = queue->data[i + 1];
		}
		queue->rear--;
	}

	return valueRemoved;
}

// (6) Get the front element
int getFront(Queue_t* queue) {
	// check if the queue is empty
	if (isQueueEmpty(queue)) {
		perror("Queue is empty");
		return -1;
	}
	// return the front element
	return queue->data[queue->front];
}

// (7) Get the rear element
int getRear(Queue_t* queue) {
	// check if the queue is empty
	if (isQueueEmpty(queue)) {
		perror("Queue is empty");
		return -1;
	}
	// return the rear element
	return queue->data[queue->rear];
}

// (8) Print the queue
void printQueue(Queue_t* queue) {
	// check if the queue is empty
	if (isQueueEmpty(queue)) {
		perror("Queue is empty");
		return;
	}
	// print the elements in the queue
	for (int i = queue->front; i <= queue->rear; i++) {
		printf("%d ", queue->data[i]);
	}
	printf("\n");
}

// ====================================
// stack functions
// ====================================

// (1) Initialize the stack

void initStack(Stack_t* stack) {
	stack->top = -1;
	memset(stack->data, 0, sizeof(stack->data));
}

// (2) Check if the stack is empty
int isStackEmpty(Stack_t*stack) {
	return stack->top == -1;
}

// (3) Check if the stack is full
int isStackFull(Stack_t* stack) {
	return stack->top == MAX_NODES - 1;
}

// (4) Push an element

void push(Stack_t* stack, int valueAdded) {
	// check if there is space in the stack
	if (isStackFull(stack)) {
		perror("Stack is full");
		return;
	}

	// add the element to the stack
	stack->top++;
	stack->data[stack->top] = valueAdded;
}

// (5) Pop an element

int pop(Stack_t* stack) {
	// check if the stack is empty
	if (isStackEmpty(stack)) {
		perror("Stack is empty");
		return -1;
	}

	// get the element from the top of the stack and decrease the top
	int poppedValue = stack->data[stack->top];
	stack->top--;

	return poppedValue;
}

// (6) Get the top element
int getTop(Stack_t* stack) {
	// check if the stack is empty
	if (isStackEmpty(stack)) {
		perror("Stack is empty");
		return -1;
	}

	// return the top element
	return stack->data[stack->top];
}

// (7) Print the stack

void printStack(Stack_t* stack) {
	// check if the stack is empty
	if (isStackEmpty(stack)) {
		perror("Stack is empty");
		return;
	}
	// print the elements in the stack
	// this is in the order that will pop the elements
	for (int i = stack->top; i >= 0; i--) {
		printf("%d ", stack->data[i]);
	}

	printf("\n");
}

// ====================================
// Graph functions
// =====================================

// (1) Initialize the graph
void initGraph(Graph_t* graph) {
	graph->nr_of_nodes = 0;
	for (int i = 0; i < MAX_NODES; i++) {
		for (int j = 0; j < MAX_NODES; j++) {
			graph->adjacency_matrix[i][j] = 0;
		}
	}
}

// (2) print graph
void printGraph(Graph_t* graph) {
	for (int i = 0; i < graph->nr_of_nodes; i++) {
		for (int j = 0; j < graph->nr_of_nodes; j++) {
			printf("%d ", graph->adjacency_matrix[i][j]);
		}
		printf("\n");
	}
}

// (3) check if the graph is empty
int isGraphEmpty(Graph_t* graph) {
	return graph->nr_of_nodes == 0;
}

// (4) check if the graph is full
int isGraphFull(Graph_t* graph) {
	return graph->nr_of_nodes == MAX_NODES;
}

// (5) add an edge to the graph
void addArc(Graph_t* graph, int node1, int node2){
	// check if edge is already present
	if (isArc(graph, node1, node2)) {
		printf("Edge already present\n");
		return;
	}
	graph->adjacency_matrix[node1][node2] = 1;
	graph->adjacency_matrix[node2][node1] = 1; 
}

// (6) remove an edge from the graph
void removeArc(Graph_t* graph, int node1, int node2) {
	// check if there is an edge between the two nodes
	if (isArc(graph, node1, node2)) {
		graph->adjacency_matrix[node1][node2] = 0;
		graph->adjacency_matrix[node2][node1] = 0; // for undirected graph
	}
	else {
		printf("No edge between the two nodes");
	}
}

// (7) check if there is an edge between two nodes
int isArc(Graph_t* graph, int node1, int node2) {
	return graph->adjacency_matrix[node1][node2] == 1;
}

// (8) get the degree of a node
int getDegree(Graph_t* graph, int node) {
	int degree = 0; // initialize the degree to 0

	for (int i = 0; i < graph->nr_of_nodes; i++) {
		if (graph->adjacency_matrix[node][i] == 1) {
			degree++; // increment the degree for each neighbor
		}
	}

	return degree;
}

// (9) get the neighbors of a node
void getNeighbors(Graph_t* graph, int node, int* neighbors, int *count) {
	(*count) = 0; // initialize the count of neighbors to 0

	for (int i = 0; i < graph->nr_of_nodes; i++) {
		if (graph->adjacency_matrix[node][i] == 1) {
			neighbors[(*count)++] = i; // add the neighbor node to the array
		}
	}

	return neighbors;
}

// (10) get the number of nodes
int getNrOfNodes(Graph_t* graph) {
	return graph->nr_of_nodes;
}

// (11) get the number of edges
int getNrOfEdges(Graph_t* graph) {
	int nr_of_edges = 0;

	// we check only the upper triangle of the adjacency matrix
	for (int i = 0; i < graph->nr_of_nodes; i++) {
		for (int j = i + 1; j < graph->nr_of_nodes; j++) {
			if (graph->adjacency_matrix[i][j] == 1) {
				nr_of_edges++;
			}
		}
	}

	return nr_of_edges;
}

// (12) read the graph from a file with the adjacency matrix
void readGraphFromFile_AdjancecyMatrix(Graph_t* graph, char* filename, int *start, int *end) {
	FILE* fin = fopen(filename, "r");

	if (fin == NULL) {
		perror("Error opening file");
		return;
	}

	// read the number of nodes
	fscanf(fin, "%u", &graph->nr_of_nodes);

	// read the adjacency matrix
	for (int i = 0; i < graph->nr_of_nodes; i++) {
		for (int j = 0; j < graph->nr_of_nodes; j++) {
			fscanf(fin, "%u", &graph->adjacency_matrix[i][j]);
		}
	}

	// read the start and end nodes
	fscanf(fin, "%d", start);
	fscanf(fin, "%d", end);

	fclose(fin);
}

// (13) read the graph from a file with the arcs
void readGraphFromFile_Arcs(Graph_t* graph, char* filename, int *start, int *end) {
	FILE* fin = fopen(filename, "r");

	if (fin == NULL) {
		perror("Error opening file");
		return;
	}

	initGraph(graph); // initialize the graph

	// read the number of nodes
	fscanf(fin, "%u", &graph->nr_of_nodes);
	
	int node1, node2;
	// read the arcs
	while (fscanf(fin, "%d %d", &node1, &node2) == 2) {
		// add the arc to the graph
		graph->adjacency_matrix[node1][node2] = 1;
		graph->adjacency_matrix[node2][node1] = 1; // for undirected graph
	}

	// read the start and end nodes
	printf("Enter start and end nodes: ");
	scanf("%d %d", start, end);

	fclose(fin);
}

// BFS -> Breadth First Search -> cuprindere -> coada
 
void bfs(Graph_t graph, int start) {
	unsigned visited[MAX_NODES] = { 0 }; // this is the array for visited nodes

	Queue_t queue; // this is the queue for the BFS
	initQueue(&queue); // initialize the queue

	// enqueue the start node
	enqueue(&queue, start);
	visited[start] = 1; // mark the start node as visited

	while (!isQueueEmpty(&queue)) {
		int currentNode = dequeue(&queue); // get the current node

		printf("Visiting node %d\n", currentNode); // print the current node

		// visit the neighbors of the current node
		for (int i = 0; i < graph.nr_of_nodes; i++) {
			// check the neighbours node
			if (graph.adjacency_matrix[currentNode][i] == 1 && visited[i] == 0) {
				// enqueue the neighbor node
				enqueue(&queue, i);
				visited[i] = 1; // mark the neighbor node as visited
			}
		}
	}
}

// BFS is used to find the shortest path in an unweighted graph 

void shortest_path(Graph_t graph, int start, int destination) {

	unsigned visited[MAX_NODES] = { 0 }; // this is the array for visited nodes
	int parent[MAX_NODES]; // this is the array for the path

	// initialize the queue
	Queue_t queue;
	initQueue(&queue);

	// enqueue the start node
	enqueue(&queue, start);
	visited[start] = 1; // mark the start node as visited

	// in path we ll store the parent of the current node
	parent[start] = -1; // set the path for the start node to -1

	// now we ll dequeue the elements from the queue in order to visit the nodes

	while (!isQueueEmpty(&queue)) {
		// at first iteration this we ll be the start node
		int currentNode = dequeue(&queue); // get the current node
		//printf("Visiting node %d\n", currentNode); // print the current node

		// check if the current node is the destination node
		if (currentNode == destination) {
			// or we can use a function to print the path
			break;
		}

		// visit the neighbors of the current node
		for (int i = 0; i < graph.nr_of_nodes; i++) {
			// check if the node is connected to the current node

			if (graph.adjacency_matrix[currentNode][i] == 1 && visited[i] == 0) {
				// enqueue the neighbor node
				enqueue(&queue, i);
				visited[i] = 1; // mark the neighbor node as visited
				parent[i] = currentNode; // set the path for the neighbor node
			}
		}
	}

	if (!visited[destination]) {
		printf("No path found\n");
		return;
	}

	int pathForPrint[MAX_NODES]; // this is the array for the path to be printed
	int pathIndex = 0; // this is the index for the path to be printed

	// we start from destination, ignore the element -1(it reach the start node) and we go to the start node
	for (int i = destination; i != -1; i = parent[i]){
		pathForPrint[pathIndex++] = i;
	}

	printf("Path from %d to %d: ", start, destination);
	for (int i = pathIndex - 1; i >= 0; i--) {
		printf("%d ", pathForPrint[i]);
	}
	printf("\n");
}

// bfs recursive

// asta e singura cu gpt)))))))))
void bfsLevel(const Graph_t* g, int frontier[], int cnt, int visited[]) {
	int next[MAX_NODES], nextCnt = 0;

	// Pentru fiecare nod în frontieră, vizitează vecinii nevizitați
	for (int idx = 0; idx < cnt; idx++) {
		int u = frontier[idx];
		for (int v = 0; v < g->nr_of_nodes; v++) {
			if (g->adjacency_matrix[u][v] && !visited[v]) {
				visited[v] = 1;
				printf("Visiting node %d\n", v);
				next[nextCnt++] = v;
			}
		}
	}
	// Recursiv, la nivelul următor
	if (nextCnt > 0) {
		bfsLevel(g, next, nextCnt, visited);
	}
}

void BFSRecursive(const Graph_t* g, int start) {
	int visited[MAX_NODES] = { 0 };
	visited[start] = 1;
	printf("Visiting node %d\n", start);

	int frontier[1] = { start };
	bfsLevel(g, frontier, 1, visited);
}



// DFS -> Depth First Search -> adancime -> stiva

void dfs(Graph_t graph, int start) {
	unsigned visited[MAX_NODES] = { 0 }; // this is the array for visited nodes

	Stack_t stack; // this is the stack for the DFS
	initStack(&stack); // initialize the stack

	// push the start node
	push(&stack, start);
	//visited[start] = 1; // mark the start node as visited

	while (!isStackEmpty(&stack)) {
		// get the current node
		int currentNode = pop(&stack);
		

		if (visited[currentNode] == 1) {
			continue; // if the node is already visited, skip it
		}
		printf("Visiting node %d\n", currentNode + 1); // print the current node
		visited[currentNode] = 1; // mark the current node as visited

		// visit the neighbors of the current node
		for (int i = (graph.nr_of_nodes - 1); i >= 0; i--) {
			// check the arcs
			if (graph.adjacency_matrix[currentNode][i] == 1 && visited[i] == 0) {
				push(&stack, i); // push the neighbor node
				//visited[i] = 1; // mark the neighbor node as visited
			}
		}
	}
}

// recursive function DFS

void dfsRecursive(Graph_t graph, int start, int *visited) {
	//unsigned visited[MAX_NODES] = { 0 }; 
	visited[start] = 1; // mark the neighbor node as visited
	printf("Visiting node %d\n", start + 1); // print the current node


	for (int i = 0; i < graph.nr_of_nodes; i++) {
		if (graph.adjacency_matrix[start][i] == 1 && visited[i] == 0) {
			dfsRecursive(graph, i, visited); // call the function recursively
		}
	}

	//for (int i = (graph.nr_of_nodes - 1); i >= 0; i--) {
	//	if (graph.adjacency_matrix[start][i] == 1 && visited[i] == 0) {
	//		dfsRecursive(graph, i, visited); // call the function recursively
	//	}
	//}
}

// conex commponents -> we can use DFS or BFS to find the connected components

// FIRST : BFS

void bfsComponent(Graph_t graph, int start, unsigned visited[], int nr_of_components) {
	Queue_t queue;
	initQueue(&queue);

	enqueue(&queue, start);
	visited[start] = 1;

	printf("Component %d: %d ",nr_of_components, start); // print the current node

	while (!isQueueEmpty(&queue)) {
		int currentNode = dequeue(&queue);

		for (int i = 0; i < graph.nr_of_nodes; i++) {
			if (graph.adjacency_matrix[currentNode][i] == 1 && visited[i] == 0) {
				enqueue(&queue, i);
				visited[i] = 1;

				printf("%d ", i); // print the current node
			}
		}
	}
}

int conexComponentsWithBFS(Graph_t graph) {
	unsigned visited[MAX_NODES] = { 0 }; // this is the array for visited nodes
	int nr_of_components = 0; 

	for (int i = 0; i < graph.nr_of_nodes; i++) {
		// we want to apply the bfsComponent function only on the unvisited nodes
		// this way we ll find every subgraph that is connected
		// and it will be more efficient
		if (visited[i] == 0) {
			nr_of_components++;
			bfsComponent(graph, i, visited, nr_of_components);
		}
	}

	return nr_of_components;
}

// SECOND : DFS

void dfsComponent(Graph_t graph, int start, unsigned visited[], int nr_of_components) {
	Stack_t stack;
	initStack(&stack);

	push(&stack, start);
	visited[start] = 1;

	printf("Component %d: %d ", nr_of_components, start); // print the current node

	while (!isStackEmpty(&stack)) {
		int currentNode = pop(&stack);

		for (int i = (graph.nr_of_nodes - 1); i >= 0; i--) {
			if (graph.adjacency_matrix[currentNode][i] == 1 && visited[i] == 0) {
				push(&stack, i);
				visited[i] = 1;
				printf("%d ", i); // print the current node
			}
		}
	}
}	

int conexComponentsWithDFS(Graph_t graph) {
	unsigned visited[MAX_NODES] = { 0 }; // this is the array for visited nodes
	int nr_of_components = 0;

	for (int i = 0; i < graph.nr_of_nodes; i++) {
		// we want to apply the dfsComponent function only on the unvisited nodes
		// this way we ll find every subgraph that is connected
		// and it will be more efficient
		if (visited[i] == 0) {
			nr_of_components++;
			dfsComponent(graph, i, visited, nr_of_components);
		}
	}
	
	return nr_of_components;
}

// count paths
void countPaths_aux(Graph_t graph, int start, int end, int *path_count, int *visited) {
	if (start == end) {
		(*path_count)++;
		return;
	}

	visited[start] = 1;

	for (int i = 0; i < graph.nr_of_nodes; i++) {
		if (graph.adjacency_matrix[start][i] == 1 && visited[i] == 0) {
			countPaths_aux(graph, i, end, path_count, visited);
		}
	}

	visited[start] = 0; // backtrack
}

int countPaths(Graph_t graph, int start, int end) {
	unsigned visited[MAX_NODES] = { 0 }; // this is the array for visited nodes
	int path_count = 0;

	countPaths_aux(graph, start, end, &path_count, visited);

	return path_count;
}


// ====================================
// Main function
// ====================================
int main(int argc, char** argv) {
	// check for command line arguments
	if (argc != 2) {
		perror("Usage: ./program <filename>");
		return 1;
	}

	// create the graph
	Graph_t graph;
	int start, end;
	// read the graph from the file
	readGraphFromFile_AdjancecyMatrix(&graph, argv[1], &start, &end);

	// read the graph from the file
	//readGraphFromFile_Arcs(&graph, argv[1], &start, &end);

	// print the adjacency matrix
	printf("=====================================\n");
	printf("Adjacency matrix:\n");
	printGraph(&graph);
	printf("=====================================\n");


	printf("=====================================\n");
	// call the bfs function
	printf("BFS:\n");
	bfs(graph, start);
	printf("=====================================\n");

	printf("=====================================\n");
	// for the shortest path from 0 to 3
	printf("Shortest path from %d to %d:\n", start, end);
	shortest_path(graph, start, end);
	printf("=====================================\n");

	printf("=====================================\n");
	// call the dfs function
	printf("DFS:\n");
	dfs(graph, 0);
	printf("=====================================\n");

	printf("=====================================\n");
	// call the bfs function for the connected components
	printf("Connected components with BFS:\n");
	int nr_of_components = conexComponentsWithBFS(graph);
	printf("Number of connected components: %d\n", nr_of_components);
	printf("=====================================\n");

	printf("=====================================\n");
	// call the dfs function for the connected components
	printf("Connected components with DFS:\n");
	nr_of_components = conexComponentsWithDFS(graph);
	printf("Number of connected components: %d\n", nr_of_components);
	printf("=====================================\n");

	printf("=====================================\n");
	// call the count paths function
	printf("Count paths from %d to %d:\n", start, end);
	int path_count = countPaths(graph, start, end);
	printf("Number of paths: %d\n", path_count);
	printf("=====================================\n");

	printf("=====================================\n");
	// call the dfs function recursive
	printf("DFS recursive:\n");
	unsigned visited[MAX_NODES] = { 0 }; // this is the array for visited nodes
	dfsRecursive(graph, 0, visited);
	printf("=====================================\n");

	printf("=====================================\n");
	// call the bfs function recursive
	printf("BFS recursive:\n");
	BFSRecursive(&graph, start);
	printf("=====================================\n");

	printf("=====================================\n");
	// print neighbours
	int neighbors[MAX_NODES];
	int count = 0;
	getNeighbors(&graph, start, neighbors, &count);
	printf("Neighbors of %d: ", start);
	for (int i = 0; i < count; i++) {
		printf("%d ", neighbors[i]);
	}
	printf("\n");
	printf("=====================================\n");

	printf("=====================================\n");
	// print nr of edges
	printf("Number of edges: %d\n", getNrOfEdges(&graph));
	printf("=====================================\n");


	return 0;
}