#include <stdio.h>
#include <stdlib.h>
#define MAX_LEVEL 10

// int succesor(int st[], int k, int n){
//     if (st[k]<n){
//         st[k]++;
//         return 1;
//     }
//     else{
//         return 0;
//     }
// }
int eValid(int st[], int k) {
  for (int i = 1; i < k; i++) {
    if (st[i] == st[k]) {
      return 0;
    }
  }
  return 1;
}

int solutie(int st[], int k, int n) { return k == n; }

void afiseazaSol(int st[], int k, int n) {
  for (int i = 1; i <= k; i++) {
    printf("%d ", st[i]);
  }
  printf("\n");
}

void back_rec(int st[], int k, int n) {
  if (k >= MAX_LEVEL) {
    perror("depasirea stivei locale\n");
    return;
  }
  for (int i = 1; i <= n; i++) { // acestia sunt succesorii posibili
    st[k] = i;                   // pune acel succesor pe nivel
    if (eValid(st, k)) {
      if (solutie(st, k, n)) {
        afiseazaSol(st, k, n);
      } else {
        back_rec(st, k + 1, n); // rec ~ k=k+1
        /*daca avem o configuratie partiala, valida, dar care
        nu e solutie (~inca nu e destul) --> trebuie sa trecem
        la nivelul urmator
        */
      }
    } else {
      ; // daca nu e valid doar se va trece la urmatorul
    }
  }
  /* la incehiere for-ului se incheie apelul curent de functie
  --> se continua de pe "nivelul" anterior (din stack)
  */
}

int main(int argc, char *argv[]) {

  if (argc < 2)
    return -1;
  int n = atoi(argv[1]);

  int st[MAX_LEVEL] = {0};
  back_rec(st, 1, n);
  return 0;
}
