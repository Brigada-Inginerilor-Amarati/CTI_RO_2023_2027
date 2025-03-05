/*
Sa se implementeze:

A) un program C, folosind apeluri sistem si functii de biblioteca care se apeleaza sub forma ./executabil entry, unde entry este o cale catre un fisier obisnuit.

Programul va verifica faptul ca a primit minim un argument; in caz contrar, va afisa pe stderr un mesaj de utilizare.

Procesul parinte va crea un proces fiu si ii va transmite acestuia continutul fisierului primit ca si argument printr-un pipe. Procesul fiu va filtra din continutul primit de la parinte doar acele linii care incep cu majuscula si le va trimite printr-un pipe parintelui (filtrarea se va face OBLIGATORIU prin executarea unei comenzi). Parintele va contoriza numarul total de majuscule primite de la fiu. La incheierea cu situatie de eroare a procesului fiu, parintele va afisa pe stderr un mesaj de forma: 

" Procesul fiu cu PID-ul <PID> s-a incheiat cu codul <cod>". La final, va afisa pe ecran contorul de majuscule.

Procesul fiu si procesul parinte vor rula obligatoriu in paralel.

Se vor trata cazurile de eroare pentru apelurile sistem folosite.

Functiile de biblioteca permise sunt DOAR pentru formatări (printf).

B) un shell script care se apeleaza sub forma bash script entry1 entry2 ...

Script-ul va verifica faptul ca a primit minim un argument; in caz contrar, va afisa un mesaj de utilizare.

Considerand doar argumentele care indica catre fisiere obisnuite valide, script-ul va calcula numarul total de majuscule care fac parte din linii incepand cu o majuscula. In acest scop, va executa programul de la punctul A) pentru fiecare astfel de argument. La final va afisa pe ecran acest numar.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>

#define M_BUFF 4096

struct sigaction action;
pid_t pid;
int p1[2], p2[2];
char buff[M_BUFF];

void end_child()
{
    int status;
    wait(&status);
    if (!WIFEXITED(status))
    {
        perror("Error: abnormal child");
        exit(8);
    }
    dup2(2, 1);
    printf("Procesul cu PID-ul %d s-a incheiat cu codul %d.", pid, WEXITSTATUS(status));
    dup2(1, 1);
}

void parent(char *entry)
{
    int file = open(entry, O_RDONLY);
    int s;

    action.sa_handler = end_child;
    if (sigaction(SIGCHLD, &action, NULL) < 0)
    {
        perror("Error: sigaction");
        exit(6);
    }

    close(p1[0]);
    close(p2[1]);
    while ((s = read(file, buff, M_BUFF)))
    {
        if (write(p1[1], buff, s) < 0)
        {
            perror("Error: write");
            exit(4);
        }
    }
    if (s < 0)
    {
        perror("Error: read");
        exit(5);
    }
    close(p1[1]);
    int c = 0;
    while ((s = read(p2[0], buff, M_BUFF)))
    {
        for(int i=0; i<s; i++)
        {
            if(buff[i] >= 'A' && buff[i] <= 'Z' )
                c++;
        }
    }
    if (s < 0)
    {
        perror("Error: read");
        exit(5);
    }
    printf("%d", c);
}

void child()
{
    dup2(p1[0], 0);
    dup2(p2[1], 1);
    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]);
    execlp("grep", "grep", "^[A-Z]", NULL);
}

int main(int argc, char *argv[])
{
    if (argc < 1)
    {
        dup2(2, 1);
        printf("Usage: %s <entry>", argv[0]);
        exit(-1);
    }
    else
    {
        struct stat myStat;
        if (lstat(argv[1], &myStat) < 0)
        {
            perror("Error: lstat");
            exit(1);
        }
        if (!S_ISREG(myStat.st_mode))
        {
            dup2(2, 1);
            printf("Usage: %s <regular_file>", argv[0]);
            exit(-1);
        }
        if (pipe(p1) < 0)
        {
            perror("Error: pipe");
            exit(2);
        }
        if (pipe(p2) < 0)
        {
            perror("Error: pipe");
            exit(2);
        }
        if ((pid = fork()) < 0)
        {
            perror("Error: fork");
            exit(3);
        }
        if (pid == 0)
        {
            parent(argv[1]);
        }
        else
        {
            child();
        }
    }
    return 0;
}