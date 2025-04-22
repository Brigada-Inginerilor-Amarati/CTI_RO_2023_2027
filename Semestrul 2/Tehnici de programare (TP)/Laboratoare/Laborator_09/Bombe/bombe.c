#include "bombe.h"

struct BOMB{
    int x;
    int y;
    int raza;
    int este_explodata;
};

Bomb_t citeste_bombe_din_fisier(int *n, int *k, FILE *fin){
    if(fscanf(fin, "%d %d", n, k) != 2){
        printf("Nu avem suficiente date \n");
        return NULL;
    }

    int x, y, raza;

    Bomb_t bombe = malloc(*n * sizeof(struct BOMB));
    if (bombe == NULL){
        return NULL;
    }

    for(int i = 0; i < *n; i++){
        if(fscanf(fin, "%d %d %d", &x, &y, &raza) != 3){
            return NULL;
        }

        bombe[i].x = x;
        bombe[i].y = y;
        bombe[i].raza = raza;
        bombe[i].este_explodata = 0;
    }

    return bombe;
}

void print_bombe_info(Bomb_t bombe, int n){
    for(int i = 0; i < n; i++){
        printf("x : %d - y : %d - raza : %d - stadiu %d \n", bombe[i].x, bombe[i].y, bombe[i].raza, bombe[i].este_explodata);
    }
}

int este_in_raza(Bomb_t b1, Bomb_t b2){
    int x = b1->x - b2->x;
    int y = b1->y - b2->y;
    
    return x * x + y * y <= b1->raza * b1->raza;
}

void explozie(Bomb_t bombe, int n, int k, int *nr_bombe_explodate){
    bombe[k].este_explodata = 1;
    
    for(int i = 0; i < n; i++){
        if(bombe[i].este_explodata == 0 && este_in_raza(&bombe[k], &bombe[i])){
            //bombe[i].este_explodata = 1;
            (*nr_bombe_explodate)++;
            explozie(bombe, n,i, nr_bombe_explodate);
        }
    }
}

