/*1. Argument: director.
2. PARinte:
    afiseaza "." pana la terminarea tuturor fiilor,
    afiseaza codurile de retur pe masura ce se termina fiecare fiu.
3. COP1:
    transmite intrarile din director catre COP2.
4. COP2:
    filtreaza liniile ce contin fisiere obisnuite,
    le transmite catre COP3.
5. COP3:
    numara liniile primite.
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#define CLOSE_READ 0
#define CLOSE_WRITE 1

int nrProcese = 3, p1[2], p2[2];
pid_t pid;

void close_pipe(int pipe, int read_write)
{
    if (pipe == 1)
    {
        if (close(p1[read_write]) < 0)
        {
            perror("eroare la inchiderea pipe-ului");
            exit(10);
        }
    }
    else if (pipe == 2)
    {
        if (close(p2[read_write]) < 0)
        {
            perror("eroare la inchiderea pipe-ului");
            exit(20);
        }
    }
}

void COP1(char *director)
{
    sleep(1);
    close_pipe(1, CLOSE_READ);
    close_pipe(2, CLOSE_READ);
    close_pipe(2, CLOSE_WRITE);
    dup2(p1[1], 1);
    close_pipe(1, CLOSE_WRITE);
    //execlp("ls -l", "ls -l", director, NULL);
    execlp("ls", "ls", "-al", director, NULL);
    exit(100);
}

void COP2()
{
    sleep(5);
    close_pipe(1, CLOSE_WRITE);
    close_pipe(2, CLOSE_READ);

    dup2(p1[0], 0);
    close_pipe(1, CLOSE_READ);

    dup2(p2[1], 1);
    close_pipe(2, CLOSE_WRITE);

   
    execlp("bash", "bash", "program.sh", NULL);
    exit(200);
}

void COP3()
{
    sleep(9);
    close_pipe(1, CLOSE_READ);
    close_pipe(1, CLOSE_WRITE);
    close_pipe(2, CLOSE_WRITE);

    dup2(p2[0], 0);
    close_pipe(2, CLOSE_READ);

    execlp("wc", "wc", "-l", NULL);
    exit(300);
}



void proces_par_OnChild(int sig)
{
    int status;
    int pidChild = wait(&status);
    if (!WIFEXITED(status))
    {
        perror("ERROR: Procesul-copil s-a terminat anormal\n");
        exit(2);
    }
    printf("\npid-ul :%d s a incheiat, la statuts %d \n", pidChild, WEXITSTATUS(status));
    nrProcese--;

    if (nrProcese == 0)
    {
        printf("\nParent ends.\n");
        exit(0);
    }
}

void proces_parinte()
{
    struct sigaction action;
    memset(&action, 0X00, sizeof(struct sigaction));
    action.sa_handler = proces_par_OnChild;

    if (sigaction(SIGCHLD, &action, NULL) < 0)
    {
        perror("child sigaction error");
        exit(1);
    }
    close_pipe(1, CLOSE_READ);
    close_pipe(1, CLOSE_WRITE);
    close_pipe(2, CLOSE_READ);
    close_pipe(2, CLOSE_WRITE);
    while (1)
    {
        printf("...");
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("eroare la nr argumente");
        exit(1);
    }

    struct stat DirStat;
    if (lstat(argv[1], &DirStat) < 0)
    {
        perror("eroare la lstat");
        exit(2);
    }
    if (!(S_ISDIR(DirStat.st_mode)))
    {
        printf("nu e dir");
        exit(3);
    }

    if (pipe(p1) < 0)
    {
        perror("eroare pipe1");
        exit(4);
    }

    if (pipe(p2) < 0)
    {
        perror("eroare pipe2");
        exit(5);
    }

    for (int i = 0; i < 3; i++)
    {
        if ((pid = fork()) < 0)
        {
            perror("Eroare la fork\n");
            exit(1);
        }
        if (pid == 0)
        {
            if (i == 0)
                COP1(argv[1]);
            if (i == 1)
                COP2();
            if (i == 2)
                COP3();
        }
    }
    proces_parinte();
    return 0;
}