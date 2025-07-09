#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// ----------------
// Defines
// ----------------

#define DEBUG 1

// ----------------
// Structura de date
// ----------------

typedef struct ArboreBinar{
    int parinte;
    struct ArboreBinar* left;
    struct ArboreBinar* right;
}AB_T;

typedef AB_T* ArboreBinar_T;

int main(int argc, char** argv){
    if(argc != 2){
        perror("Incorrect number of arguments. Usage: ./ArboreBinarParinte <filename>\n");
        return 1;
    }

    
    return 0;
} 