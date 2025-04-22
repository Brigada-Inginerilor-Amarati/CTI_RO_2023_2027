// Aplicația 3.8: Folosind funcții polimorfice, să se implementeze o colecție
// eterogenă de produse. Vor fi 2 tipuri de produse: ​calculatoare,​
// definite prin {nume CPU, capacitate memorie în GB} și ​monitoare,​
// definite prin {diagonală în inch, rezoluție orizontală, rezoluție verticală}.
// Singura funcție polimorfică va fi ​afisare,​ care afișează tipul și
// toate proprietățile unui produs pe o linie. De exemplu, dacă avem un
// calculator și un monitor, afișarea va fi de forma: calculator: cpu:Ryzen,
// memorie:8GB monitor: diagonala:24, rezolutie:1920x1080

#include "products.h"

int main(void)
{

  factory_t factory = init_factory();

  product_t *products[2] = {NULL, NULL};

  products[0] = factory.generate_pc("Ryzen", 8);

  products[1] = factory.generate_monitor(24, 1920, 1080);

  products[0]->show_data(products[0]);
  products[1]->show_data(products[1]);

  free(products[0]);
  free(products[1]);

  return 0;
}
