#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 16

typedef struct{
    int lungime;
    char culoare[MAX_LEN];
}Cub_t;

Cub_t *cuburi;

int cmp(const void *a, const void *b){
    Cub_t p1 = *(Cub_t *) a;
    Cub_t p2 = *(Cub_t *) b;

    if(p1.lungime < p2.lungime){
        return -1;
    }

    if(p1.lungime > p2.lungime){
        return 1;
    }

    return 0;
}

int avemSuccesor(int stiva[], int nr_cuburi, int k){
    if (stiva[k] < nr_cuburi)
    {
        stiva[k]++;
        return 1;
    }

    return 0;
}

int eValid(int stiva[], int k){
    for (int i = 1; i < k; i++) {
        if (stiva[i] == stiva[k]) {
            return 0; // cuburi trebuie să fie distincte
        }
    }

    if(k > 1){
        //printf("%d %d \n", cuburi[stiva[k] - 1].lungime, cuburi[stiva[k - 1] - 1].lungime);
        if(cuburi[stiva[k] - 1].lungime <= cuburi[stiva[k - 1] - 1].lungime){
            return 0;
        }
        if(strcmp(cuburi[stiva[k] - 1].culoare, cuburi[stiva[k - 1] - 1].culoare) == 0){
            return 0;
        }
    }
    
    return 1;
}

int eSolutie(int stiva[], int k, int nr_minim_turnuri){
    return k >= nr_minim_turnuri;
}

void afisare(int stiva[], int k){
    for(int i = 1; i <= k; i++){
        printf("%d - %s, ", cuburi[stiva[i] - 1].lungime, cuburi[stiva[i] - 1].culoare);
    }

    printf("\n--\n");
}
void back(int nr_cuburi, int nr_minim_turnuri){
    int stiva[30] = {0};
    int k = 1;
    stiva[k] = 0;

    

    while (k > 0)
    {
        if(avemSuccesor(stiva, nr_cuburi, k)){
            if(eValid(stiva, k)){
                if(eSolutie(stiva, k, nr_minim_turnuri)){
                    afisare(stiva, k);
                    k++;
                }
                else{
                    k++;
                    stiva[k] = 0;
                }
            }
            else{
                ;
            }
        }
        else{
            k--;
        }
    }
    

}


int main(int argc, char **argv){

    if(argc != 2){
        return -1;
    }

    FILE *fin = fopen(argv[1], "r");

    if(fin == NULL){
        return -2;
    }
    
    int nr_cuburi = 0;
    int nr_minim_turnuri = 0;

    fscanf(fin, "%d %d", &nr_cuburi, &nr_minim_turnuri);

    cuburi = malloc(nr_cuburi * sizeof(Cub_t));

    if(cuburi == NULL){
        return -3;
    }

    for(int i = 0; i < nr_cuburi; i++){
        Cub_t cub_to_add = {0, ""};
        int x = 0;
        char y[MAX_LEN] = "";

        fscanf(fin, "%d ", &x);
        cub_to_add.lungime = x;

        fgets(y, MAX_LEN, fin);
        y[strcspn(y, "\n")] = 0;

        strncpy(cub_to_add.culoare, y, MAX_LEN - 1);
        cuburi[i] = cub_to_add;
    }

    qsort(cuburi, nr_cuburi, sizeof(Cub_t), cmp);

    for(int i = 0; i < nr_cuburi; i++){
        printf("%d - %s\n", cuburi[i].lungime, cuburi[i].culoare);
    }

    fclose(fin);

    back(nr_cuburi, nr_minim_turnuri);

    return 0;
}