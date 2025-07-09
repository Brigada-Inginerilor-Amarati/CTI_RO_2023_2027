#include <stdio.h>
#include <stdint.h>
#include "IndicatorParinte.h"


TTree InitTree(TTree a) {
	// initializeaza fiecare nod cu 0
	for (int i = 0; i < MAXNODES; i++) {
		a.nodes[i].parent = 0;
		a.nodes[i].key = 0;
	}

	a.size = 0;

	return a;
}

TTree InsertNode(TTree a, TNodeRef  parent, TKey key) {
	// crestem size-ul arborelui
	a.size++;


	// adaugam nodul la sfarsitul arborelui
	a.nodes[a.size].key = key;
	a.nodes[a.size].parent = parent;

	return a;
}

void printArray(TTree a) {

	printf("\n----------------Arbore printat : --------------------\n");

	printf("\nIndex: ");
	// cate noduri avem in arbore
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", i);
	}

	printf("\nKey:   ");
	// afisam valorile nodurilor -> key
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", a.nodes[i].key);
	}

	printf("\nParent:");
	// afisam parintii nodurilor
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", a.nodes[i].parent);
	}

	printf("\n-----------------------------------------------------\n");
}

void printNode(TNode node, char* message) {
	printf("\n%s Key: %d, Parent: %d\n", message, node.key, node.parent);
}

// gaseste parintele in O(1)
TNodeRef parent(TTree a, TNodeRef noderef) {
	return a.nodes[noderef].parent;
}

// verifica daca arborele este gol si returneaza radacina(index 1)
TNodeRef getRoot(TTree a) {
	if (a.size < 1) {
		return 0;
	}

	return 1;
}

// gaseste indexul nodului in arbore
TNodeRef findNodeIndex(TTree a, TNode node) {
	for (uint8_t i = 0; i <= a.size; i++) {
		if (a.nodes[i].key == node.key && a.nodes[i].parent == node.parent) {
			return i;
		}
	}

	// daca nu exista nodul in arbore
	return 0;
}

// gaseste primul copil al unui nod
TNodeRef firstChild(TTree a, TNodeRef index) {	// index ul este indexul parintelui
	if (!index) {
		return 0;
	}

	for (uint8_t i = 1; i <= a.size; i++) {
		if (a.nodes[i].parent == index) {
			return i;
		}
	}

	return 0;
}

// gaseste cheia unui nod
TKey nodeKey(TTree a, TNodeRef noderef) {	// noderef este indexul nodului
	if (noderef > a.size) {
		return 0;
	}

	return a.nodes[noderef].key;
}

// gaseste nodul dupa index
TNode nodeByRef(TTree a, TNodeRef noderef) {	// noderef este indexul nodului
	return a.nodes[noderef];
}


// gaseste fratele din dreapta
TNodeRef rightSibling(TTree a, TNodeRef noderef) {	// noderef este indexul nodului
	if (!noderef) {
		return 0;
	}

	for (TNodeRef i = noderef + 1; i <= a.size; i++) {
		if (a.nodes[i].parent == a.nodes[noderef].parent) {
			return i;
		}
	}

	return 0;
}

// sterge un nod din arbore
TTree deleteNode(TTree a, TNodeRef noderef) {
	a.nodes[noderef].key = 0;
	a.nodes[noderef].parent = 0;

	// stergem toti copii nodului
	for (TNodeRef i = noderef; i <= a.size; i++) {
		if (a.nodes[i].parent == noderef) {
			a.nodes[i].key = 0;
			a.nodes[i].parent = 0;
		}
	}

	for (TNodeRef i = noderef; i <= a.size; ) {
		if (a.nodes[i].parent == 0 && a.nodes[i].key == 0) {
			for (TNodeRef j = i + 1; j <= a.size; j++) {
				if (a.nodes[j].parent > i) {
					a.nodes[j].parent--;
				}
				
				// mutam nodurile in stanga
				a.nodes[j - 1] = a.nodes[j];
			}

			a.size--;
		}

		if (a.nodes[i].parent != 0 && a.nodes[i].key != 0) {
			i++;
		}
	}

	printArray(a);

	return a;
}

// parcurgere preordine
void preOrderRecursiv(TTree arbore, TNodeRef radacinaCurenta) {		// radacinaCurenta -> indexul la care ne aflam
	// merge si fara asta
	/*if (radacinaCurenta == 0) {
		return;
	}*/

	// ne luam nodul curent
	TNode nodCurent = nodeByRef(arbore, radacinaCurenta);

	// afisam nodul curent -> doar cheia pentru usurinta
	printf("%d ", nodCurent.key);

	// luam primul copil al nodului(asta va fi cel mai din stanga)
	TNodeRef primulCopil = firstChild(arbore, radacinaCurenta);

	if (primulCopil == 0) {
		return;	
	}
	
	preOrderRecursiv(arbore, primulCopil);

	// acum mergem la fratele din dreapta
	TNodeRef frateDreapta = rightSibling(arbore, primulCopil);

	while (frateDreapta != 0) {
		preOrderRecursiv(arbore, frateDreapta);
		frateDreapta = rightSibling(arbore, frateDreapta);
	}
}

// simplificat preOrder

void parcurgerePreordine(TTree arbore, TNodeRef radacinaCurenta) {
	TNode nodCurent = nodeByRef(arbore, radacinaCurenta);

	printf("%d ", nodCurent.key);

	TNodeRef primulCopil = firstChild(arbore, radacinaCurenta);

	while (primulCopil != 0) {
		parcurgerePreordine(arbore, primulCopil);
		primulCopil = rightSibling(arbore, primulCopil);
	}
}

void postOrderRecursiv(TTree arbore, TNodeRef radacinaCurenta) {
	/*if (radacinaCurenta == 0) {
		return;
	}*/

	TNodeRef primulCopil = firstChild(arbore, radacinaCurenta);

	if (primulCopil != 0) {
		//apelam recursiv pentru primul copil
		postOrderRecursiv(arbore, primulCopil);
	}

	TNodeRef frateDreapta = rightSibling(arbore, primulCopil);

	// apelam recursiv pentru fiecare frate din dreapta
	while (frateDreapta != 0) {
		postOrderRecursiv(arbore, frateDreapta);
		frateDreapta = rightSibling(arbore, frateDreapta);
	}

	// ne luam nodul curent
	TNode nodCurent = nodeByRef(arbore, radacinaCurenta);

	// afisam nodul curent -> doar cheia pentru usurinta

	printf("%d ", nodCurent.key);
}


// mai putin cod aici
void parcurgerePostordine(TTree arbore, TNodeRef radacinaCurenta) {
	TNodeRef primulCopil = firstChild(arbore, radacinaCurenta);

	while (primulCopil != 0) {
		parcurgerePostordine(arbore, primulCopil);
		primulCopil = rightSibling(arbore, primulCopil);
	}

	TNode nodCurent = nodeByRef(arbore, radacinaCurenta);

	printf("%d ", nodCurent.key);
}

void inOrderRecursiv(TTree arbore, TNodeRef radacinaCurenta) {
	TNodeRef primulCopil = firstChild(arbore, radacinaCurenta);

	if (primulCopil != 0) {
		inOrderRecursiv(arbore, primulCopil);
	}

	// ne luam nodul curent
	TNode nodCurent = nodeByRef(arbore, radacinaCurenta);

	printf("%d ", nodCurent.key);

	TNodeRef frateDreapta = rightSibling(arbore, primulCopil);

	while (frateDreapta != 0) {
		inOrderRecursiv(arbore, frateDreapta);
		frateDreapta = rightSibling(arbore, frateDreapta);
	}
}

