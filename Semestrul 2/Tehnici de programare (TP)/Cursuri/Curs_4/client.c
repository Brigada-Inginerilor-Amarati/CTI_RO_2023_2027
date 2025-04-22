#include <stdio.h>
#include "stiva.h"

int main(){


	//int TEST=666;
	printStatus();
	TEST=7777;
	printStatus();

	Stiva_t st=makeStack();
	if (!st){
		printf("problma la crearea stivei");
		return -1;
	}
	

	for (int i=1; i<=10; i++){
		int x=i*12;
		if (push(st, x)!=STIVA_OK){
			perror("eroare la inserarea elementului\n");
		}
		Element_t aux=0;
		if (peek(st, &aux)==STIVA_OK){
			printf("Elemetnul din varf este %u", aux);
		}
		else{
			perror("eraoare la peek\n");
		}
	}
	for (int i=1; i<=5; i++){
		Element_t aux=0;
		if (pop(st, &aux)==STIVA_OK){
			printf("am scos din varf %u\n", aux);
		}
	}

	destroyStack(st);
    return 0;
}