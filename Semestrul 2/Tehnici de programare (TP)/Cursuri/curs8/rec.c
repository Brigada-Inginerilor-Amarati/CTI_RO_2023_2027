#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void print_reverse(void)
{
  int n;
  scanf("%d", &n);

  if (n != 0)
    print_reverse();

  printf("%d ", n);
}

int calc_prefix(void)
{
  // citeste de la intrare o expresie in notatie prefix -> operanzii sunt valori
  // de o singura cifra

  int c = getchar();

  if (isdigit(c))
  {
    return c - '0';
  }

  int Ed = calc_prefix();
  int Es = calc_prefix();

  switch (c)
  {
  case '+':
    return Es + Ed;
  case '-':
    return Es - Ed;
  case '*':
    return Es * Ed;
  case '/':
    return Es / Ed;
  default:
    return 0;
  }
}

void print_matrix(int a[][10], int nL, int nC)
{
  for (int i = 0; i < nL; i++)
  {
    for (int j = 0; j < nC; j++)
    {
      printf("%d ", a[i][j]);
    }
    printf("\n");
  }
}

void fill(int a[][10], int nL, int nC, int i, int j)
{

  print_matrix(a, nL, nC);

  printf("\n.........................................");

  // celula valida
  if (i >= 0 && i < nL && j >= 0 && j < nC)
  {
    if (a[i][j] == 1) // uscat
    {
      a[i][j] = 9; // marcam ca fiind uscat vizitat

      fill(a, nL, nC, i - 1, j); // deplasare in sus
      fill(a, nL, nC, i + 1, j); // deplasare in jos
      fill(a, nL, nC, i, j - 1); // deplasare la stanga
      fill(a, nL, nC, i, j + 1); // deplasare la dreapta
    }
  }
}

int main(void)
{

  int a[][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                 {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
                 {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
                 {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
                 {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
                 {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
                 {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
                 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}

  };

  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      if (a[i][j] == 1)
        fill(a, 10, 10, 0, 0);

  return 0;
}
