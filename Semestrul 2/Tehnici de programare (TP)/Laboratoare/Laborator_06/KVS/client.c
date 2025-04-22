#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "kvs.h"

int main(void)
{
clock_t start, end;
  double cpu_time_used;
  
  KVS_t data = initKVS();

  El_t elem;
  elem.cheie = 10;
  elem.valoare = 5;

  start = clock();

  data = adauga(data, elem);

  end = clock();
  cpu_time_used = ((double)(end - start) / CLOCKS_PER_SEC);
  //printf("%f\n", cpu_time_used);

  elem.cheie = 7;
  elem.valoare = 12;

  data = adauga(data, elem);

  
  
  start = clock();

  int x = cauta(data, 10);
  printf("%d \n", x);

  //printKVS(data);

  end = clock();
  cpu_time_used = ((double)(end - start) / CLOCKS_PER_SEC);
  //printf("%f\n", cpu_time_used);

  //printf("%d %d\n", cauta(data, 10), cauta(data, 7));
  
  free(data);

  return 0;

}