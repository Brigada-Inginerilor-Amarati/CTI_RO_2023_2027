// Aplicația 3.5: Să se implementeze o funcție care tabelează o funcție
// matematică de un parametru, primită ca argument. Funcția tabelată primește un
// parametru de tip ​double ​și returnează o valoare tot de tip
// ​double​. Funcția de tabelare va primi ca parametri: ​a și ​b -
// capetele de tip ​double ale intervalului închis de tabelat, ​n - un
// număr întreg care arată în câte segmente egale se împarte intervalul
// ​[a,b]​, incluzând capetele acestuia și f - funcția de tabelat. Să se
// testeze funcția de tabelare cu valori ​a,b și n citite de la tastatură,
// tabelând funcțiile ​cos,​ ​sqrt ș​ i ​fabs din ​math.h
// Exemplu :​ tabelare(-10, 10, 20, fabs)​ va afișa pe câte o linie valori
// de forma ​f(-10) = 10​ ​f(-9) = 9​ ... ​f(10) = 10

#include <math.h>
#include <stdio.h>

void tabelare(double a, double b, int segments, double (*f)(double))
{

  double step = (fabs(a) + fabs(b)) / segments;
  for (double i = a; i < b; i += step)
    printf("%9.5f | %9.5f\n", i, f(i));
}

int main(void)
{
  double a = -10.2552, b = 10.66;
  int segments = 50;
  tabelare(a, b, segments, sin);

  return 0;
}
