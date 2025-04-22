#include <stdio.h>
#include <stdlib.h>

int main(void) {

  int n = 6;

  if (n % 2)
    goto odd;
  else
    goto even;

  goto end;

odd:
  printf("Odd\n");

even:
  printf("Even\n");

end:
  return 0;
}
