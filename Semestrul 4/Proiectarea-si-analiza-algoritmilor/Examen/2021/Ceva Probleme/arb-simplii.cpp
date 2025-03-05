// arb simplii.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
#include <iostream>

using namespace std;


struct Nod {
	int cheie;
	int parinte;
};

Nod arb[20];
int apar[20];

void afisare(int n) {
	int i;
	for (i = 0; i < n; i++)
		cout << arb[i].parinte<<" ",
		apar[arb[i].parinte] ++;
	cout << endl;

	for (i = 0; i < n; i++)
		cout << arb[i].cheie << " ";
	cout << endl;
}
int main()
{
	int n = 0;

	arb[n].parinte = 0;
	arb[n].cheie = 1; n++;

	arb[n].parinte = 1;
	arb[n].cheie = 2; n++;

	arb[n].parinte = 1;
	arb[n].cheie = 3; n++;

	arb[n].parinte = 1;
	arb[n].cheie = 4; n++;

	arb[n].parinte =1;
	arb[n].cheie = 5; n++;

	afisare(n);
	int max=-1, i;
	for (i = 0; i < 20; i++) {
		if (apar[i] > max) max = apar[i];
	}
	cout << "Gradul arborelui: " << max<<endl;
	return 0;
}

