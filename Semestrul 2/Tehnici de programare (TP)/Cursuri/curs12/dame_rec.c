#include <stdio.h>
#include <stdlib.h>

int eValid(int st[], int k) {
  for (int i = 1; i < k; i++) {
    if (st[i] == st[k]) {
      return 0;
    }
    if (abs(st[i] - st[k]) == abs(i - k)) {
      return 0;
    }
  }
  return 1;
}

int eSolutie(int st[], int k, int n) { return k == n; }

void afiseazaTabla(int st[], int k) {
  for (int i = 1; i <= k; i++) {
    printf("%d ", st[i]);
  }
  printf("\n\n");

  for (int ln = 1; ln <= k; ln++) {
    for (int col = 1; col <= k; col++) {
      if (col == st[k - ln + 1]) {
        putchar('X');
      } else {
        putchar('-');
      }
    }
    putchar('\n');
  }
  for (int i = 1; i <= k + 10; i++)
    putchar('=');
  putchar('\n');
  getchar();
}

void dame_recursiv(int k, int n, int st[]) {

  for (int i = 1; i <= n; i++) {
    st[k] = i;
    if (eValid(st, k)) {
      if (eSolutie(st, k, n)) {
        afiseazaTabla(st, k);
      } else {
        dame_recursiv(k + 1, n, st);
      }
    } else {
      ; // elementul invalid se ignora: se va trece la urmatorul
    }
  }
  // nu se coboara explicit (k--) din stiva caci este rezolvat de mecanismul de
  // recursivitate
}

int main(int argc, char *argv[]) {

  int st[100] = {0};
  dame_recursiv(1, atoi(argv[1]), st);

  return 0;
}
