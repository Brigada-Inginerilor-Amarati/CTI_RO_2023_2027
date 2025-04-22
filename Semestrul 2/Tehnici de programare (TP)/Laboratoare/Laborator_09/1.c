/*
1. Numere în format hexazecimal. Scrieţi o funcţie care 

returnează valoarea unui număr natural citit de la intrare 

caracter cu caracter, în format hexazecimal (cifrele 0-9, A-F sau a-f).


Indicaţii: problema e similară cu funcţia readnat de la curs. 

Un prim test se face pentru cifra hexazecimala (isxdigit, tot din ctype.h), 

apoi pentru a obţine valoarea cifrei trebuie tratat diferit cazul cifrelor şi 

al literelor (de la A la F). Cum scrierea cu litere mari sau mici nu contează se 

poate folosi funcţia toupper din ctype.h (returnează literă mare dacă argumentul e 

literă mică; altfel returnează chiar litera dată ca argument) pentru a trata cele

două cazuri uniform. (La fel de bine se poate folosi funcţia pereche tolower).

Pentru o variantă mai simplă, presupuneţi că în scriere se foloseşte doar un 

singur fel de litere (mari sau mici). 

*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_LEN 16

int hex_to_dec(int numar){
    char c;

    c = getc(stdin);

    if (!isxdigit(c))
    {
        return numar;
    }
    
    if(isdigit(c)){
        numar = numar * 16 + (c - '0');
    }
    if(isalpha(c)){
        c = toupper(c);
        numar = numar * 16 + (c - 'A') + 10;
    }

    return hex_to_dec(numar);
}


int main(void){
    int nr = 0;
    nr = hex_to_dec(nr);

    printf("%d \n", nr);
    return 0;
}