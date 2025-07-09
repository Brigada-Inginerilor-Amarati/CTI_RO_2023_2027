#include <stdio.h>
#include <stdbool.h>

// =========================================================
// Constants
// =========================================================

// Maximum number of nodes in the graph
#define MAX_NODES 50 

int main(void){
    // N - number of nodes (current vertices)
    // A - number of edges (arcs)
    int N, A;

    bool graph[MAX_NODES][MAX_NODES] = {false}; // Adjacency matrix

    int i, j;

    int node1, node2;

    // Read the number of nodes and edges

    printf("Enter the number of nodes: ");
    if(scanf("%d %d", &N, &A) != 2 || N < 1 || N > MAX_NODES || A < 0 || A > (N * (N - 1) / 2)){
        perror("Invalid input for number of nodes or edges.");
        return 1;
    }

    // initialize the adjacency matrix
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            graph[i][j] = false;
        }
    }

    // mark the diagonal as true
    for(i = 0; i < N; i++){
        graph[i][i] = true;
    }

    // read pairs of nodes
    printf("Enter the %d arcs (pairs of nodes):\n", A);
    for(i = 0; i < A; i++){
        if(scanf("%d %d", &node1, &node2) != 2){
            perror("Invalid input for nodes.\n");
            return 1;
        }

        graph[node1][node2] = true;
        graph[node2][node1] = true; // undirected graph
    }

    // print the adjacency matrix

    printf("Adjacency matrix:\n");
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    return 0;
}