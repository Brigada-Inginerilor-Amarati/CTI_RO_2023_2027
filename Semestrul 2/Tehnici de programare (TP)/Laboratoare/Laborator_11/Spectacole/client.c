#include "spectacole.h"


int main(void){
    FILE *fin = NULL;
    if((fin = fopen("in.txt", "r")) == NULL){
        return -1;
    }
    int n = 0;

    Spectacol_t *spectacole = citeste_ore(fin, &n);

    print_data(spectacole, n);

    qsort(spectacole, n, sizeof(Spectacol_t), cmp_end_hour);

    int cnt = alege_spectacole(spectacole, n);

    printf("%d \n", cnt);

    free(spectacole);
    fclose(fin);

    return 0;
}