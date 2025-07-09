#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// =========================================================
// Constants
// =========================================================

// Maximum number of nodes in the graph
#define MAX_NODES 50

// ==========================================================
// structures
// ==========================================================

typedef int Key_t;
typedef void* Info_t;

typedef struct {
    Key_t key;
    Info_t info;
} Node_T;

// table of nodes

typedef Node_T Graph_Table_T[MAX_NODES];

// matrix adjacency

typedef bool Graph_Matrix_T[MAX_NODES][MAX_NODES];

// structure of the graph

typedef struct {
    Graph_Table_T nodes;
    Graph_Matrix_T arcs;
    int num_nodes;          // number of nodes
} Graph_T;

// structure of arcs

typedef struct Arc{
    int line;
    int column;
}Arc_T;

// =========================================================
// Functions
// =========================================================

// (1) create a void graph

void Init_Graph(Graph_T *graph){
    graph->num_nodes = 0;

    // the key and info would be overwritten when the node is added and the adjacency matrix is initialized
    for(int i = 0; i < MAX_NODES; i++){
        graph->nodes[i].key = 0;
        graph->nodes[i].info = NULL;
        for(int j = 0; j < MAX_NODES; j++){
            graph->arcs[i][j] = false;
        }
    }

    // or we can use memset
    // memset(graph->nodes, 0, sizeof(Graph_Table_T));
    // memset(graph->arcs, 0, sizeof(Graph_Matrix_T));
}

// (2) check if the graph is empty

bool Is_Empty_Graph(Graph_T *graph){
    return graph->num_nodes == 0;
}

// (3) check if the graph is full
bool Is_Full_Graph(Graph_T *graph){
    return graph->num_nodes >= MAX_NODES;
}

// (4) search for a k key in the graph -> return true if found, false otherwise

bool Search_Key_In_Graph(Graph_T *graph, Key_t key_Searched){
    // check if the graph is empty
    if(Is_Empty_Graph(graph)){
        return false;
    }

    for(int i = 0; i < graph->num_nodes; i++){
        if(graph->nodes[i].key == key_Searched){
            return true;
        }
    }
    return false;
}
// (5) indicate the index of the node with the key k in the graph

void Indicate_Node_Index(Graph_T *graph, Key_t key_Searched, int *index){
    // check if the graph is empty
    if(Is_Empty_Graph(graph)){
        *index = -1;
        return;
    }

    for(int i = 0; i < graph->num_nodes; i++){
        if(graph->nodes[i].key == key_Searched){
            *index = i;
            return;
        }
    }

    *index = -1;
}

// (6) indicate arc 

void Indicate_Arc(const Graph_T *graph, Key_t key1, Key_t key2, Arc_T *arc){
    int index1 = -1;
    int index2 = -1;

    Indicate_Node_Index(graph, key1, &index1);
    Indicate_Node_Index(graph, key2, &index2);

    if(index1 >= 0 && index2 >= 0 && graph->arcs[index1][index2]){
        arc->line = index1;
        arc->column = index2;
    }
    else{
        arc->line = -1;
        arc->column = -1;
    }
}

// (7) add a node to the graph -> info are not ordered
void Insert_Node(Graph_T *graph, Node_T node_Inserted){
    // check if the graph is full
    if(Is_Full_Graph(graph)){
        perror("Graph is full");
        return;
    }

    // check if the node is already in the graph
    if(Search_Key_In_Graph(graph, node_Inserted.key)){
        perror("Node already exists");
        return;
    }

    // now we can add the node to the graph

    // increase the number of nodes
    graph->num_nodes++;

    // put the node in the graph
    graph->nodes[graph->num_nodes - 1] = node_Inserted;

    //initialize the new line and column of the adjacency matrix

    for(int i = 0; i < graph->num_nodes; i++){
        // initialize the line
        graph->arcs[graph->num_nodes - 1][i] = false;

        // initialize the column
        graph->arcs[i][graph->num_nodes - 1] = false;
    }

    graph->arcs[graph->num_nodes - 1][graph->num_nodes - 1] = true;
    
}

// (8) remove a node from the graph -> unordered

void Remove_Node(Graph_T *graph, int index){
    // check if the graph is empty
    if(Is_Empty_Graph(graph)){
        perror("Graph is empty");
        return;
    }

    // check if the index is valid
    if(index < 0 || index >= graph->num_nodes){
        perror("Index is invalid");
        return;
    }

    // move the last node to the index of the node to be removed
    graph->nodes[index] = graph->nodes[graph->num_nodes - 1];

    // move the last line of the adjacency matrix to the index of the node to be removed
    for(int i = 0; i < graph->num_nodes; i++){
        graph->arcs[index][i] = graph->arcs[graph->num_nodes - 1][i];
    }

    // move the last column of the adjacency matrix to the index of the node to be removed
    for(int i = 0; i < graph->num_nodes; i++){
        graph->arcs[i][index] = graph->arcs[i][graph->num_nodes - 1];
    }

    // decrease the number of nodes
    graph->num_nodes--;
}

// (9) add an arc to the graph

void Insert_Arc(Graph_T *graph, Key_t key1, Key_t key2){
    // get the index of the nodes
    int index1 = -1;
    int index2 = -1;

    Indicate_Node_Index(graph, key1, &index1);
    Indicate_Node_Index(graph, key2, &index2);

    // add the arc to the adjacency matrix
    if(index1 >= 0 && index2 >= 0){
        graph->arcs[index1][index2] = true;
    }
    else{
        perror("Arc cannot be added");
        return;
    }
}

// (10) remove an arc from the graph

void Remove_Arc(Graph_T *graph, Arc_T arc){
    // check if the arc is valid
    if(arc.line < 0 || arc.line >= graph->num_nodes || arc.column < 0 || arc.column >= graph->num_nodes){
        perror("Arc is invalid");
        return;
    }

    // remove the arc from the adjacency matrix
    graph->arcs[arc.line][arc.column] = false;
    graph->arcs[arc.column][arc.line] = false;
}

// (11) print the graph
void Print_Graph(Graph_T *graph){
    // check if the graph is empty
    if(Is_Empty_Graph(graph)){
        perror("Graph is empty");
        return;
    }

    printf("Graph:\n");
    for(int i = 0; i < graph->num_nodes; i++){
        printf("%d ", graph->nodes[i].key);
    }

    printf("\n");

    printf("Adjacency matrix:\n");

    for(int i = 0; i < graph->num_nodes; i++){
        for(int j = 0; j < graph->num_nodes; j++){
            printf("%d ", graph->arcs[i][j]);
        }
        printf("\n");
    }
}

// ==========================================================
// Main function
// ==========================================================

int main(void){
    Graph_T graph;
    Init_Graph(&graph);

    // insert 4 nodes
    Insert_Node(&graph, (Node_T){10, NULL});
    Insert_Node(&graph, (Node_T){20, NULL});
    Insert_Node(&graph, (Node_T){30, NULL});
    Insert_Node(&graph, (Node_T){40, NULL});

    // connect 10 -> 20, 20 -> 30, 30 -> 40
    Insert_Arc(&graph, 10, 20);
    Insert_Arc(&graph, 20, 30);
    Insert_Arc(&graph, 30, 40);
    
    // print the graph
    Print_Graph(&graph);
    printf("\n");

    // remove the node 20
    int index = -1;
    Indicate_Node_Index(&graph, 20, &index);
    Remove_Node(&graph, index);
    printf("After removing node 20:\n");
    Print_Graph(&graph);
    printf("\n");


    return 0;
}