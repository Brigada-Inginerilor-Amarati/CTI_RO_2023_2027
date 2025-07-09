#include <stdio.h>
#include <stdlib.h>

// =========================================================
// defines
// =========================================================

#define MAX_NODES 100

// =========================================================
// structures
// =========================================================

typedef struct Node{
    int name;
    struct Node* next_node;
}Node_t;

// adjacency list

Node_t* adjacency_list[MAX_NODES];

// =========================================================
// functions
// =========================================================

Node_t* create_node(int name){
    Node_t* new_node = (Node_t*)malloc(sizeof(Node_t));
    if(new_node == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    new_node->name = name;
    new_node->next_node = NULL;
    return new_node;
}

// insert a node at the beginning of the list
void insert_node(int index, int name){
    Node_t* new_node = create_node(name);

    new_node->next_node = adjacency_list[index];

    adjacency_list[index] = new_node;
}

void print_Graph(){
    printf("List of adjacency:\n");

    for(int i = 0; i < MAX_NODES; i++){
        if(adjacency_list[i] != NULL){
            printf("Node %d: ", i);
            Node_t* current = adjacency_list[i];
            while(current != NULL){
                printf("%d -> ", current->name);
                current = current->next_node;
            }
            printf("NULL\n");
        }
    }
}

int main(void){
    int N, A;
    // read the number of nodes and edges
    printf("Enter the number of nodes and edges: ");
    if(scanf("%d %d", &N, &A) != 2 || N <= 0 || N > MAX_NODES || A < 0){
        printf("Invalid input\n");
        return 1;
    }

    // initialize the adjacency list
    for(int i = 0; i < N; i++){
        adjacency_list[i] = NULL;
    }

    // read the edges
    printf("Enter the edges (node1 node2):\n");
    for(int i = 0; i < A; i++){
        int node1, node2;
        if(scanf("%d %d", &node1, &node2) != 2 || node1 < 0 || node1 >= N || node2 < 0 || node2 >= N){
            printf("Invalid edge\n");
            return 1;
        }
        insert_node(node1, node2);
        insert_node(node2, node1); // for undirected graph
    }

    // print the adjacency list
    print_Graph();
    return 0;
}
