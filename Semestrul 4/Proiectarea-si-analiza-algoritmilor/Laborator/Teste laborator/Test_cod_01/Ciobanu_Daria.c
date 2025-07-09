#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "ArbGenFirstChildRightSibling.h"

void cerintaDoi(TTree a) {
	if (a.size < 1) {
		return;
	}

	for (uint8_t i = 1; i <= a.size; i++) {
		printf("%u %u %u, ", a.nodes[i].key, a.nodes[i].firstChild, a.nodes[i].rightSibling);
	}
	//printf("\n");
}

void parcurgereInPreordine(TTree a, TNodeRef indexRadacina) {
	printf("%u ", a.nodes[indexRadacina].key);

	TNodeRef firstChild = a.nodes[indexRadacina].firstChild;

	while (firstChild != 0) {
		parcurgereInPreordine(a, firstChild);
		firstChild = a.nodes[firstChild].rightSibling;
	}
}



void parcurgereInInordine(TTree a, TNodeRef indexRadacina) {
	if (firstChild(a, indexRadacina)) {
		parcurgereInInordine(a, firstChild(a, indexRadacina));
	}

	printf("%u ", a.nodes[indexRadacina].key);

	TNodeRef frateDreapta = rightSibling(a, firstChild(a, indexRadacina));

	while (frateDreapta) {
		parcurgereInInordine(a, frateDreapta);
		frateDreapta = rightSibling(a, frateDreapta);
	}
}

void parcurgereInPostOrdine(TTree a, TNodeRef indexRadacina) {
	TNodeRef firstChild = a.nodes[indexRadacina].firstChild;

	while (firstChild != 0) {
		parcurgereInPostOrdine(a, firstChild);
		firstChild = a.nodes[firstChild].rightSibling;
	}

	printf("%u ", a.nodes[indexRadacina].key);
}

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("Incorrect ussage of arguments \n");
		return 1;
	}

	FILE* fin = fopen(argv[1], "r");

	if (fin == NULL) {
		printf("File could not be open!\n");
		return 2;
	}

	TTree arb = { 0 };
	arb = InitTree(arb);

	TKey key = 0;
	TNodeRef parent = 0;
	// radacina
	fscanf(fin, "%hhd %hhd", &parent, &key);
	arb = InsertNode(arb, 0, key);

	while (fscanf(fin, "%hhd %hhd", &parent, &key) == 2) {
		//printf("Inserted values : %d %d\n", key, parent);
		arb = InsertNode(arb, parent, key);
	}

	char c[3] = { 0 };
	strcpy(c, argv[2]);

	//printf("%s", c);


	if (strcmp(c, "A") == 0) {
		cerintaDoi(arb);
	}
	else if (strcmp(c, "P") == 0) {
		parcurgereInPreordine(arb, 1);
	}
	else if (strcmp(c, "I") == 0) {
		parcurgereInInordine(arb, 1);
	}
	else if (strcmp(c, "O") == 0) {
		parcurgereInPostOrdine(arb, 1);
	}


	//printArray(arb);


	return 0;
}