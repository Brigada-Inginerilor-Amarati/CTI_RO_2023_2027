// Aplicația 3.3: ​Să se implementeze o funcție c​ are primește ca
// parametri un vector de întregi, numărul elementelor din vector transmis prin
// adresă și un predicat care testează dacă un întreg îndeplinește o anumită
// condiție. Funcția va sterge din vector toate elementele care nu îndeplinesc
// condiția dată și va actualiza numărul elementelor cu numărul de elemente
// rămas în vector. Să se testeze funcția cu un predicat care testează dacă un
// număr este negativ și să se afișeze vectorul rezultat.

#include <stdio.h>

int is_prime(int n)
{
  if (n < 2)
    return 0;
  for (int i = 2; i * i <= n; i++)
  {
    if (n % i == 0)
      return 0;
  }

  return 1;
}

int is_odd(int n) { return n % 2; }

int is_even(int n) { return !(n % 2); }

void remove_elements_by_condition(int *array, int *n, int (*condition)(int))
{
  int i = 0;
  int j = 0;
  while (i < *n)
  {
    if (condition(array[i]))
    {
      i++;
    }
    else
    {
      array[j++] = array[i++];
    }
  }
  *n = j;
}

void print_array(int *array, int n)
{
  for (int i = 0; i < n; i++)
    printf("%d ", array[i]);
  printf("\n");
}

int main(void)
{
  int array[] = {1, 2, 3, 4, 5};

  int n = sizeof(array) / sizeof(array[0]);

  print_array(array, n);

  remove_elements_by_condition(array, &n, is_prime);

  print_array(array, n);

  return 0;
}
