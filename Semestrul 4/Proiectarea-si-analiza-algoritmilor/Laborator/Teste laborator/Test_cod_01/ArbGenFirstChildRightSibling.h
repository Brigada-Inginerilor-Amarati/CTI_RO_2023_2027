#include<stdint.h>

#define MAXNODES 100

typedef uint8_t TKey;


// in structura nodului avem prima modificare fata de IndicatorParinte.h parinte devine primFiu si adaugam frateDreapta
typedef struct {
	uint8_t firstChild,rightSibling;
	TKey key;
}TNode;

typedef uint8_t TNodeRef;

typedef struct {
	TNode nodes[MAXNODES];
	uint8_t size; //tree size = number of nodes in the tree	
}TTree;

TTree InitTree(TTree a);

TTree InsertNode(TTree a, TNodeRef  parent, TKey key);

void printArray(TTree a);

void printNode(TNode node, char* message);

TNodeRef parent(TTree a, TNodeRef noderef);

TKey nodeKey(TTree a, TNodeRef noderef);

TNode nodeByRef(TTree a, TNodeRef noderef);

TNodeRef firstChild(TTree a, TNodeRef noderef);

TNodeRef rightSibling(TTree a, TNodeRef noderef);

TTree deleteNode(TTree a, TNodeRef noderef);

TTree insertNodePrimFiuFrateDreapta(TTree arbore, TNodeRef primFiu, TNodeRef frateDreapta, TKey key);