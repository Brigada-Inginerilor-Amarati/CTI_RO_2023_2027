/*
Scrieti un program care rezolva sudoku cu cifre de la 1-4. 

Matricea initiala este data intr-un fisier trimis ca si 

parametru de intrare, cu 0 sunt notate spatiile libere. 

Toate solutiile vor fi tiparite pe ecran.

Exemplu:
Fisier intrare:

0 0 0 3
0 1 0 4
4 2 0 0
1 0 4 0

Solutie:
2 4 1 3
3 1 2 4
4 2 3 1
1 3 4 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4

int mat[N][N];

void citire(char *nume_fisier)
{
    FILE *f = fopen(nume_fisier, "r");
    if (f == NULL)
    {
        printf("Fisierul nu exista\n");
        exit(1);
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            fscanf(f, "%d", &mat[i][j]);

    fclose(f);
}

void afisare()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

int valid(int x, int y, int val)
{
    for (int i = 0; i < N; i++)
        if (mat[x][i] == val || mat[i][y] == val)
            return 0;

    int x0 = x / 2 * 2, y0 = y / 2 * 2;
    for (int i = x0; i < x0 + 2; i++)
        for (int j = y0; j < y0 + 2; j++)
            if (mat[i][j] == val)
                return 0;

    return 1;
}

void sudoku(int x, int y)
{
    if (x == N)
    {
        afisare();
        return;
    }

    if (mat[x][y] == 0)
    {
        for (int i = 1; i <= N; i++)
            if (valid(x, y, i))
            {
                mat[x][y] = i;
                if (y == N - 1)
                    sudoku(x + 1, 0);
                else
                    sudoku(x, y + 1);
                mat[x][y] = 0;
            }
    }
    else
    {
        if (y == N - 1)
            sudoku(x + 1, 0);
        else
            sudoku(x, y + 1);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Numar gresit de argumente\n");
        exit(1);
    }

    citire(argv[1]);
    sudoku(0, 0);

    return 0;
}