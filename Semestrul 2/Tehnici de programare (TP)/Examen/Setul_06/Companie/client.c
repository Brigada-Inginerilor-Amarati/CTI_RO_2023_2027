#include "companie.h"


int main(void){
    Companie_t comp = create_companie("Hella");

    Proiect_t proiect1 = create_proiect("Pr Alpha", HIGH_PRIORITY);
    Proiect_t proiect2 = create_proiect("Pr Beta", HIGH_PRIORITY);

    add_proiect_to_companie(comp, proiect1);
    add_proiect_to_companie(comp, proiect2);

    Angajat_t ang1 = create_angajat("Daria", SOFTWARE, proiect1);
    Angajat_t ang2 = create_angajat("Maria", TESTARE, proiect1);
    Angajat_t ang3 = create_angajat("Dan", MANAGEMENT, proiect1);

    Angajat_t ang4 = create_angajat("Ion", SOFTWARE, proiect2);
    Angajat_t ang5 = create_angajat("Anisia", TESTARE, proiect2);
    Angajat_t ang6 = create_angajat("Ileana", MANAGEMENT, proiect2);

    add_angajat_to_proiect(proiect1, ang1);
    add_angajat_to_proiect(proiect1, ang2);
    add_angajat_to_proiect(proiect1, ang3);

    add_angajat_to_proiect(proiect2, ang4);
    add_angajat_to_proiect(proiect2, ang5);
    add_angajat_to_proiect(proiect2, ang6);

    add_angajat_to_companie(comp, ang1);
    add_angajat_to_companie(comp, ang2);
    add_angajat_to_companie(comp, ang3);
    add_angajat_to_companie(comp, ang4);
    add_angajat_to_companie(comp, ang5);
    add_angajat_to_companie(comp, ang6);

    printf("\n--------------- \n angajat \n---------------\n");

    printAngajat(ang1);

    printf("\n--------------- \n proiect \n---------------\n");

    printProiect(proiect1);

    printf("\n--------------- \n companie \n---------------\n");

    printCompanie(comp);

    printf("\n------------------------------\n");

    print_angajati_sortati(proiect1);

    printf("\n-------------------------------\n");

    int size = 0;
    Angajat_t *angajati = gaseste_angajati_dupa_departament_prioritate(comp, SOFTWARE, HIGH_PRIORITY, &size);

    printf("\n-------------------------------\n");

    free_vectorAngajati(angajati, size);

    freeCompanie(comp);


    return 0;
}