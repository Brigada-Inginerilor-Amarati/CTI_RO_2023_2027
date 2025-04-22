#include "back.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int avemSuccesor(int st[], int k, int n) {
  if (st[k] < n) {
    st[k]++;
    return 1;
  }
  return 0;
}

int eValidDame(int st[], int k) {
  // doua dame nu se pot afla pe acceasi linie din codificare (acelasi element
  // din stiva nu poate avea doua valori distincye simultan)
  for (int i = 1; i < k; i++) {
    if (abs(st[i] - st[k]) ==
        abs(i - k)) { // verificam diagonalele; delta(x)==delta(y)
      return 0;
    }
    if (st[i] == st[k]) { // doua dame nu sunt pe aceeasi coloana
      return 0;
    }
  }
  return 1;
}

int eSolutieDame(int st[], int k, int payload[]) {

  return k == payload[0]; // prin conevnetie payload[0] pastreaza n-ul problemei
}

void afiseazaDame(int st[], int k) { //!!!k==n
  for (int i = k; i >= 1; i--) {
    for (int j = 1; j <= k; j++) {
      if (j == st[i]) { // daca ne gasim pe coloana egala cu cea pe care trebuie
                        // amplasata dama
        putchar('*'); // punem un caracter conventional
      } else {
        putchar('-');
      }
    }
    putchar('\n');
  }
  printf("----------------\n");
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    return -1;
  }
  int n = atoi(argv[1]);

  printf("Dame:\n");
  int payloadDame[MAX_PAYLOAD] = {n, n};
  BackBehaviour_t behDame = {payloadDame, avemSuccesor, eValidDame,
                             eSolutieDame, afiseazaDame};
  back(behDame);

  return 0;
}
