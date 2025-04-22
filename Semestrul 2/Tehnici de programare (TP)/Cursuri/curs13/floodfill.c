#include <functional>
#include <stdio.h>
#include <stdlib.h>
#define MAX_DIM 100

int pas = 10;

void print_matrix(int a[][MAX_DIM], int lines, int columns) {
  for (int i = 0; i < lines; i++) {
    for (int j = 0; j < columns; j++)
      printf("%2d ", a[i][j]);
    printf("\n");
  }
  printf("-----------------------------\n");
}

void fill2(int a[][MAX_DIM], int lines, int columns, int i, int j) {
  if (i < 0 || i > lines - 1 || j < 0 || j > columns || a[i][j] != 0)
    return;

  int delta[] = {-1, 0, 1};

  a[i][j] = pas++;

  if (i == 0 || j == 0 || i == lines - 1 || j == columns - 1) {
    printf("am iesit din labirint la (%d %d)\n", i, j);
    print_matrix(a, lines, columns);
  }

  for (int k = 0; k < sizeof(delta) / sizeof(delta[0]); k++)
    for (int p = 0; p < sizeof(delta) / sizeof(delta[0]); p++)
      fill2(a, lines, columns, i + delta[k], j + delta[p]);

  /*
  for (int k = 0; k < sizeof(delta) / sizeof(delta[0]); k++) {
    fill2(a, lines, columns, i + delta[k], j);
    fill2(a, lines, columns, i, j + delta[k]);
    }*/

  a[i][j] = 0;
  pas--;
}

void fill(int a[][MAX_DIM], int lines, int columns, int i, int j) {

  a[i][j] = pas++;

  if (i == 0 || j == 0 || i == lines - 1 || j == columns - 1) {
    printf("am iesit din labirint la (%d %d)\n", i, j);
    print_matrix(a, lines, columns);
  }

  // N
  if (i > 0 && a[i - 1][j] == 0)
    fill(a, lines, columns, i - 1, j);

  // S
  if (i < lines - 1 && a[i + 1][j] == 0)
    fill(a, lines, columns, i + 1, j);

  // W
  if (j < columns - 1 && a[i][j + 1] == 0)
    fill(a, lines, columns, i, j + 1);

  // E
  if (j > 0 && a[i][j - 1] == 0)
    fill(a, lines, columns, i, j - 1);

  a[i][j] = 0;
  pas--;
}

int main(void) {

  int a[][MAX_DIM] = {{1, 1, 1, 0, 0, 0, 0, 1},
                      {1, 1, 1, 0, 1, 1, 0, 1},
                      {0, 0, 1, 0, 1, 0, 0, 1},
                      {0, 1, 1, 0, 1, 1, 1, 0},
                      {0, 0, 0, 0, 1, 1, 1, 0}};

  int lines = 5, columns = 8;

  fill2(a, lines, columns, 0, 3);

  print_matrix(a, lines, columns);

  return 0;
}
