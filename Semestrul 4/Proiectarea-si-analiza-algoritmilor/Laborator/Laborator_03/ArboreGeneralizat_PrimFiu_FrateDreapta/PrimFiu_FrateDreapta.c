#include <stdio.h>
#include <stdint.h>
#include "PrimFiu_FrateDreapta.h"


TTree InitTree(TTree a) {
	// initializeaza fiecare nod cu 0
	for (int i = 0; i < MAXNODES; i++) {
		a.nodes[i].primFiu = 0;
		a.nodes[i].frateDreapta = 0;
		a.nodes[i].key = 0;
	}

	a.size = 0;

	return a;
}

TTree InsertNode(TTree a, TNodeRef  parent, TKey key) {

	if (a.size >= MAXNODES - 1) return a;

	if (parent < 0 || parent > a.size) return a;

	a.size++;
	a.nodes[a.size].key = key;
	a.nodes[a.size].primFiu = 0;
	a.nodes[a.size].frateDreapta = 0;

	if (parent == 0) return a;

	TNodeRef parentIndex = parent;

	if (a.nodes[parentIndex].primFiu == 0) {
		a.nodes[parentIndex].primFiu = a.size;
		return a;
	}

	TNodeRef childIndex = a.nodes[parentIndex].primFiu;

	while (a.nodes[childIndex].frateDreapta != 0) {
		childIndex = a.nodes[childIndex].frateDreapta;
	}

	a.nodes[childIndex].frateDreapta = a.size;

	return a;
}

TTree insertNodePrimFiuFrateDreapta(TTree arbore, TNodeRef primFiu, TNodeRef frateDreapta, TKey key) {
	arbore.size++;
	arbore.nodes[arbore.size].key = key;
	arbore.nodes[arbore.size].primFiu = primFiu;
	arbore.nodes[arbore.size].frateDreapta = frateDreapta;

	return arbore;
}

void printArray(TTree a) {

	printf("\n----------------Arbore printat : --------------------\n");

	printf("\nIndex:          ");
	// cate noduri avem in arbore
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", i);
	}

	printf("\nKey:            ");
	// afisam valorile nodurilor -> key
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", a.nodes[i].key);
	}

	printf("\nPrim fiu:       ");
	// afisam fii 
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", a.nodes[i].primFiu);
	}

	printf("\nFrate dreapta:  ");
	// afisam fratii
	for (uint8_t i = 0; i <= a.size; i++) {
		printf("%5d ", a.nodes[i].frateDreapta);
	}

	printf("\n-----------------------------------------------------\n");
}

void printNode(TNode node, char* message) {
	printf("\n%s Key: %d, fiu: %d, frate: %d\n", message, node.key, node.primFiu, node.frateDreapta);
}


TNodeRef parent(TTree a, TNodeRef noderef) {
	TNodeRef i;

	for (i = 1; i <= a.size; i++) {
		// daca nodul nostru este primul fiu al nodului i
		if (a.nodes[i].primFiu == noderef) {
			return i;
		}
		// aici gasim practic fratele din stanga nodului nostru
		if (a.nodes[i].frateDreapta == noderef) {
			break;
		}
	}

	TNodeRef sibling = i;  // fratele din stanga nodului nostru

	// cat timp avem frate in dreapta
	while (a.nodes[sibling].frateDreapta) {

		// parcurge doar nodurile pana la nodul nostru

		for(TNodeRef j = 0; j < i; j++){	
			// la fiecare iteratie verificam daca nodul nostru este primul fiu al nodului j
			if (a.nodes[j].primFiu == sibling) {
				return j;
			}

			// aici gasim fratele din stanga nodului nostru
			if (a.nodes[j].frateDreapta == sibling) {
				sibling = j;
			}
		}
	}

	return 0;
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
		if (a.nodes[i].key == node.key && a.nodes[i].primFiu == node.primFiu && a.nodes[i].frateDreapta == node.frateDreapta) {
			return i;
		}
	}

	// daca nu exista nodul in arbore
	return 0;
}

// gaseste primul copil al unui nod
TNodeRef firstChild(TTree a, TNodeRef index) {	// index ul este indexul parintelui
	return a.nodes[index].primFiu;

	/*if (!index) {
		return 0;
	}*/


	/*for (uint8_t i = 1; i <= a.size; i++) {
		if (a.nodes[i].parent == index) {
			return i;
		}
	}*/

	//return 0;
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

	return a.nodes[noderef].frateDreapta;

	/*if (!noderef) {
		return 0;
	}

	for (TNodeRef i = noderef + 1; i <= a.size; i++) {
		if (a.nodes[i].parent == a.nodes[noderef].parent) {
			return i;
		}
	}

	return 0;*/
}

//TTree deleteNode(TTree a, TNodeRef noderef) {
//	
//}



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

