#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 30

typedef struct{
    char nume[MAX_LEN];
    char op1[MAX_LEN];
    char op2[MAX_LEN];
    char op3[MAX_LEN];
    char op4[MAX_LEN];
}Student_t;

Student_t *studenti;
int size = 0;



int main(int argc, char **argv){
    if(argc != 2){
        return -1;
    }

    FILE *fin = fopen(argv[1], "r");

    if(fin == NULL){
        return 1;
    }

    int contor = 0;
    char linie[MAX_LEN];

    while(fgets(linie, MAX_LEN, fin)){
        if(contor % 2 == 0){
            
        }
    }

    return 0;
}