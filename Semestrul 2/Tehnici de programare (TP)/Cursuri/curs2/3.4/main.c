// Aplicația 3.4: Se introduce un număr întreg ​n​<10 și apoi ​n
// numere de tip ​float​. Să se folosească funcția ​qsort pentru a
// sorta aceste numere în mod crescător. Se va introduce apoi un număr ​x
// ​de tip ​float.​ Folosind funcția bsearch, s​ă se determine dacă
// ​x există în vectorul sortat. Se pot consulta paginile de manual pentru
// funcțiile qsort ș​i ​bsearch.​

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

int cmp_asc(const void *a, const void *b)
{
  return (int)(*(float *)a - *(float *)b);
}

int cmp_desc(const void *a, const void *b)
{
  return (int)(*(float *)b - *(float *)a);
}

void read_count(int *n)
{
  printf("Introduceti n: ");

  if (scanf("%d", n) != 1)
  {
    fprintf(stderr, "Eroare la citirea lui n\n");
    exit(1);
  };

  if (*n < 1 || *n > MAX_SIZE)
  {
    fprintf(stderr, "n trebuie sa fie intre 1 si %d\n", MAX_SIZE);
    exit(1);
  }
}

void read_array(float *arr, int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("Introduceti v[%d]: ", i);
    if (scanf("%f", &arr[i]) != 1)
    {
      fprintf(stderr, "Eroare la citirea lui v[%d]\n", i);
      exit(1);
    }
  }
}

void sort_array(float *arr, int n, int (*cmp)(const void *, const void *))
{
  qsort(arr, (size_t)n, sizeof(float), cmp);
}

void print_array(float *arr, int n)
{
  printf("Vectorul sortat: ");

  for (int i = 0; i < n; i++)
  {
    printf("%f ", arr[i]);
  }
  printf("\n");
}

int contains(float x, float *arr, int n,
             int (*cmp)(const void *, const void *))
{
  // bsearch(const void *key, const void *base, size_t nel, size_t width, int
  // (*_Nonnull compar)(const void *, const void *))
  return (bsearch(&x, arr, (size_t)n, sizeof(float), cmp) != NULL);
}

int main(void)
{
  int n = 0;

  read_count(&n);

  float v[n];

  read_array(v, n);

  sort_array(v, n, cmp_desc);

  print_array(v, n);

  float x = 2;

  if (contains(x, v, n, cmp_desc))
    printf("Exista\n");
  else
    printf("Nu exista\n");

  return 0;
}
