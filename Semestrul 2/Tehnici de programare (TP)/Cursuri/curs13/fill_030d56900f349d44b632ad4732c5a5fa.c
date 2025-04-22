#include <stdio.h>
#define MAX_DIM 10

int pas=10;

void printMatrix(int a[][MAX_DIM], int nL, int nC){
    for (int i=0; i<nL; i++){
        for(int j=0; j<nC; j++){
            printf("%3d", a[i][j]);
        }
        printf("\n"); 
    }
    printf("---------------------\n");
}

void fill(int a[][MAX_DIM], int nL, int nC, int i, int j){
    a[i][j]=pas;
    pas++;
    if (i==0 || j==0 || i==nL-1 || j==nC-1){
        printf("Iesim din labirint la (%d, %d)\n", i, j);
        printMatrix(a, nL, nC);
    }
    if (i>0 && a[i-1][j]==0) fill(a, nL, nC, i-1, j);   //N
    if (i<nL-1 && a[i+1][j]==0) fill(a, nL, nC, i+1, j);   //S
    if (j<nC-1 && a[i][j+1]==0) fill(a, nL, nC, i, j+1);   //E
    if (j>0 && a[i][j-1]==0) fill(a, nL, nC, i, j-1);   //W
    a[i][j]=0;  //sterg urma, marcand celula la valoarea ei originala --> 
    pas--;      //permite urmatirea vizuala a tuturor traseelor 
                //(la fiecare intersectie genereaza toate posibilitatile a "o lua" pe ramifcatii)
}

void fill_cu_vect_de_deplasamente(int a[][MAX_DIM], int nL, int nC, int i, int j){
    if (i>=0 && i<=nL-1 && j>=0 && j<=nC-1 && a[i][j]==0){  //verific daca sunt intr-o celula permisa
        int delta[]={-1,0,1};                               //calculez lista de salturi
        a[i][j]=pas;
        pas++;
        if (i==0 || j==0 || i==nL-1 || j==nC-1){
            printf("Iesim din labirint la (%d, %d)\n", i, j);
            printMatrix(a, nL, nC);
        }
        for (int k=0;k<sizeof(delta)/sizeof(delta[0]); k++){
            fill(a, nL, nC, i+delta[k], j);   
            fill(a, nL, nC, i, j+delta[k]);   
        }
        
        a[i][j]=0;  //sterg urma, marcand celula la valoarea ei originala --> 
        pas--;      //permite urmatirea vizuala a tuturor traseelor 
                    //(la fiecare intersectie genereaza toate posibilitatile a "o lua" pe ramifcatii)
    }
}


int main(){

    int a[][MAX_DIM]={
        {1,1,1,0,0,0,0,1},
        {1,1,1,0,1,1,0,1},
        {0,0,1,0,1,0,0,1},
        {0,1,1,0,1,1,1,0},
        {0,0,0,0,1,1,1,0}
    };
    int nL=5, nC=8;

    printMatrix(a, nL, nC);

    fill(a, nL, nC, 0, 3);


    return 0;
}