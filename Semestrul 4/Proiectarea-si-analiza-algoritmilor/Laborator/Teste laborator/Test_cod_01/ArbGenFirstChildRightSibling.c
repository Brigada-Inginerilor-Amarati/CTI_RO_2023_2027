#include<stdio.h>
#include<stdint.h>
#include"ArbGenFirstChildRightSibling.h"


TTree InitTree(TTree a) {
	for (int i = 0; i < MAXNODES; i++) {
		a.nodes[i].firstChild = 0;
		a.nodes[i].rightSibling = 0;
		a.nodes[i].key = 0;
	}
	a.size = 0;
	return a;
}

TTree InsertNode(TTree a, TNodeRef parent, TKey key) {
	a.size++;
	a.nodes[a.size].key = key;
	a.nodes[a.size].firstChild = 0;
	a.nodes[a.size].rightSibling = 0;

	if (!a.nodes[parent].firstChild) {
		a.nodes[parent].firstChild = a.size;
		return a;
	}

	TNodeRef tempNode = a.nodes[parent].firstChild;

	while (a.nodes[tempNode].rightSibling) {
		tempNode = a.nodes[tempNode].rightSibling;
	}

	a.nodes[tempNode].rightSibling = a.size;

	return a;

}

void printArray(TTree a) {
	printf("\nIndex:        ");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", i);
	}
	printf("\nKey:          ");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", a.nodes[i].key);
	}
	printf("\nfirstChild:   ");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", a.nodes[i].firstChild);
	}
	printf("\nrightSibling: ");
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", a.nodes[i].rightSibling);
	}
	printf("\n------------------------------------");
}

void printNode(TNode node, char* message) {
	printf("\n%s Key: %d, firstChild: %d, rightSibling:%d \n", message, node.key, node.firstChild, node.rightSibling);
}
TNodeRef parent(TTree a, TNodeRef noderef) {
	TNodeRef i;
	for (i = 0; i < a.size; i++) {
		if (a.nodes[i].firstChild == noderef) return i;
		if (a.nodes[i].rightSibling == noderef) break;
	}

	TNodeRef tempNodeRef = i;
	while (a.nodes[tempNodeRef].rightSibling) {
		for (TNodeRef j = 0; j < i; j++) {
			if (a.nodes[j].firstChild == tempNodeRef) return j;
			if (a.nodes[j].rightSibling == tempNodeRef) tempNodeRef = j;

		}

		return 0;
	}
}

TNode nodeByRef(TTree a, TNodeRef noderef) {
	return a.nodes[noderef];
}

TNodeRef firstChild(TTree a, TNodeRef index) {
	return a.nodes[index].firstChild;
}

TNodeRef rightSibling(TTree a, TNodeRef noderef) {
	return a.nodes[noderef].rightSibling;
}

TKey nodeKey(TTree a, TNodeRef noderef) {
	if (noderef > a.size) return 0;
	return a.nodes[noderef].key;
}

TNodeRef getRoot(TTree a) {
	if (a.size < 1) return 0;
	return 1;
}