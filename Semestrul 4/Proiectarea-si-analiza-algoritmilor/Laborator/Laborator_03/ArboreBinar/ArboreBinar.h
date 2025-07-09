#include<stdint.h>

#define MAXNODES 100

typedef uint8_t TKey;


// in structura nodului avem prima modificare fata de IndicatorParinte.h parinte devine primFiu si adaugam frateDreapta
typedef struct {
	uint8_t primFiu, frateDreapta;
	TKey key;
}TNode;

typedef uint8_t TNodeRef;

typedef struct {
	TNode nodes[MAXNODES];
	uint8_t size; //tree size = number of nodes in the tree	
}TTree;


typedef struct BinaryTree {
	TKey key;
	struct BinaryTree* left;
	struct BinaryTree* right;
}BT;

typedef BT* BinaryTree_t;

BinaryTree_t initBinaryTree(TKey key);
BinaryTree_t convertAGtoBT(TTree ag, TNodeRef indexRadacina);
//void printBinaryTree(BinaryTree_t tree);
BinaryTree_t insertIntoBinaryTree(BinaryTree_t bt, TKey key);
BinaryTree_t insertIntoBinaryTreeRecursiv(BinaryTree_t bt, TKey key);
BinaryTree_t deleteNodeBinaryTreeOrdonat(BinaryTree_t bt, TKey key);
void parcurgerePreordineBT(BinaryTree_t bt);
void parcurgereInordineBT(BinaryTree_t bt);
void parcurgerePostordineBT(BinaryTree_t bt);
void freeBinaryTree(BinaryTree_t bt);


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

void preOrderRecursiv(TTree arbore, TNodeRef radacinaCurenta);
void postOrderRecursiv(TTree arbore, TNodeRef radacinaCurenta);
void inOrderRecursiv(TTree arbore, TNodeRef radacinaCurenta);