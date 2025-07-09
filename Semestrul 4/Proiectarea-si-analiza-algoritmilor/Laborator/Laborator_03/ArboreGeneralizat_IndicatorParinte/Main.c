#include <stdio.h>
#include "IndicatorParinte.h"

TTree readFile(FILE* fin, TTree arbore) {
	// urmatoarele doua sunt uint8_t declarate in structura
	TKey cheie = 0;
	TNodeRef parinte = 0;

	while (fscanf(fin, "%hhu %hhu", &cheie, &parinte) == 2) {
		printf("Values read: %hhu %hhu\n", cheie, parinte);

		arbore = InsertNode(arbore, parinte, cheie);
	}

	return arbore;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Incorrect ussage of arguments. Please use the following format: %s <input_file>\n", argv[0]);
		return -1;
	}

	FILE* fin = fopen(argv[1], "r");

	if (!fin) {
		printf("Could not open file %s\n", argv[1]);
		return -2;
	}

	TTree arbore = { 0 };

	// am initializat tot arborele
	arbore = InitTree(arbore);

	// citim din fisier si populam arborele
	arbore = readFile(fin, arbore);

	// afisam arborele dupa ce l-am populat
	printArray(arbore);
	

	// afisam arborele in preordine
	printf("\nAfisare arbore in preordine:\n");
	preOrderRecursiv(arbore, getRoot(arbore));
	printf("\n\n");

	// afisam arborele in postordine
	printf("\nAfisare arbore in postordine:\n");
	postOrderRecursiv(arbore, getRoot(arbore));
	printf("\n\n");

	// afisam arborele in inordine	
	printf("\nAfisare arbore in inordine:\n");
	inOrderRecursiv(arbore, getRoot(arbore));
	printf("\n\n");

	arbore = deleteNode(arbore, 2);

	fclose(fin);
	return 0;
}