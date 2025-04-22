#include "bombe.h"

int main(int argc, char** argv){
    if(argc != 2){
        return -2;
    }

    FILE* fin = NULL;
    if((fin = fopen(argv[1], "r")) == NULL){
        return -1;
    }
    int n = 0, k = 0;
    Bomb_t bombe = citeste_bombe_din_fisier(&n, &k, fin);

    print_bombe_info(bombe, n);

    int nr = 1;
    
    explozie(bombe, n, k, &nr);

    putchar('\n');
    print_bombe_info(bombe, n);
    
    printf("%d %d \n",nr,  n - nr);

    free(bombe);

    fclose(fin);
    return 0;
}