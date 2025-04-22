/*
5 (*). Se consideră o tablă de şah cu n linii şi m coloane.

La o poziţie dată se află un cal de şah, acesta putându-se deplasa pe tablă 

în modul specific acestei piese de şah (în L).

Să se determine o modalitate de parcurgere a tablei de către calul dat,

astfel încât acesta să nu treacă de două ori prin aceeaşi poziţie. 
 
Parcurgerea constă într-o matrice cu n linii și m coloane, 
 
fiecare element al matricei având valoarea pasului la care se ajunge în 
 
acel element, sau 0, dacă nu s-a ajuns.
*/

#include <stdio.h>
#include <stdlib.h>

const int di[] = {-1, 1, 2, 2, 1, -1, -2, -2};
const int dj[] = {2, 2, 1, -1, -2, -2, -1, 1};

int n, m, x, y, a[205][205], gata;

FILE *cin, *cout;

void afis()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            fprintf(cout, "%d ", a[i][j]);
        fprintf(cout, "\n");
    }
    gata = 1;
}

int inside(int i, int j)
{
    return i >= 1 && i <= n && j >= 1 && j <= m;
}

int pozdisponibile(int i, int j)
{
    int cnt = 0;
    for (int d = 0; d < 8; d++)
    {
        int inou = i + di[d];
        int jnou = j + dj[d];
        if (inside(inou, jnou) && a[inou][jnou] == 0)
            cnt++;
    }
    return cnt;
}

void calgreedy(int i, int j, int pas)
{
    int val, mini = 9999999, ii, jj;
    if (!gata)
    {
        a[i][j] = pas;
        if (pas == n * m)
            afis();
        else
            for (int d = 0; d < 8; d++)
            {
                int inou = i + di[d];
                int jnou = j + dj[d];
                if (inside(inou, jnou) && a[inou][jnou] == 0)
                {
                    val = pozdisponibile(inou, jnou);
                    if (val <= mini)
                        mini = val, ii = inou, jj = jnou;
                }
            }
        if (mini != 99999)
            calgreedy(ii, jj, pas + 1);
        a[i][j] = 0;
    }
}

int main()
{
    cin = fopen("saritura_calului1.in", "r");
    cout = fopen("saritura_calului1.out", "w");
    fscanf(cin, "%d %d %d %d", &n, &m, &x, &y);
    calgreedy(x, y, 1);
    fclose(cin);
    fclose(cout);
    return 0;
}

