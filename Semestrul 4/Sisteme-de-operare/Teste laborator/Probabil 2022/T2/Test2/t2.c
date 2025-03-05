/*
A) un shell script care se apeleaza sub forma bash script nr1 nr2 ... nrn

Script-ul va verifica faptul ca a primit minim un argument; in caz contrar, va afisa un mesaj de utilizare.

Script-ul va calcula media aritmetica a numerelor primite ca si parametru si o va afisa la iesirea standard.

 

B) un program C, folosind apeluri sistem si functii de biblioteca care se apeleaza sub forma ./executabil fisier, unde argumentul primit reprezinta o cale catre un fisier obisnuit.

Programul va verifica faptul ca a primit minim un argument; in caz contrar, va afisa un mesaj de utilizare.

Procesul parinte va crea un proces fiu si ii va transmite acestuia continutul fisierului primit ca si argument printr-un pipe. Procesul fiu va citi informatiile primite de la parinte si va memora intr-un vector toate cifrele primite. Dupa ce termina de citit, va lansa in executie script-ul de la punctul A, iar rezultatul va fi transmis printr-un pipe parintelui.

La incheierea procesului fiu, parintele va afisa un mesaj de forma: "Procesul fiu cu PID-ul <PID> s-a incheiat cu codul <cod>".

La final, parintele va afisa pe ecran media calculata de script.

Procesul fiu si procesul parinte vor rula obligatoriu in paralel.

Se vor trata cazurile de eroare pentru apelurile sistem folosite.

Functiile de biblioteca permise sunt DOAR pentru formatări (printf).
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
    exit
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
    perror("Error with grep");
    exit(1);
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