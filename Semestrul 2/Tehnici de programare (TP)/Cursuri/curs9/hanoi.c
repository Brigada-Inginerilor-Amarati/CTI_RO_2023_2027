#include <stdio.h>

void hanoi(int n, char src, char aux, char dest) {
  if (n == 1) {
    printf("%c --> %c\n", src, dest);
    return;
  }

  hanoi(n - 1, src, dest, aux);
  printf("%c --> %c\n", src, dest);
  hanoi(n - 1, aux, src, dest);
}

int main(void) {
  hanoi(3, 'A', 'B', 'C');
  return 0;
}
