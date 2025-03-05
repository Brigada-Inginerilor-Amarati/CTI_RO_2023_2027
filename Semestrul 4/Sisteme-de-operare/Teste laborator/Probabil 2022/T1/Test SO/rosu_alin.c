/*
Sa se implementeze un program C, folosind apeluri sistem si functii de biblioteca, care se apeleaza sub forma: ./executabil out_file text1 text2 ….
Se va verifica faptul ca exista cel putin doua argumente: primul argument reprezinta calea catre un fisier obisnuit, iar celelalte sunt siruri de caractere. In caz de erori la numarul sau tipul argumentelor, se vor afisa mesaje de utilizare corespunzatoare. 
Se va crea un proces fiu care va parcurge lista de argumente (cu exceptia primului argument, care este fisierul de iesire) si va scrie in out_file fiecare text de 100 de ori. 
Procesul parinte va crea o data pe secunda cate o noua legatura simbolica (numita “link_<n>”, unde<n> este numarul de ordine, incepand de la 1) spre fisierul out_file, pana la terminarea procesului fiu, dupa care se termina si el.
Inainte de terminare, procesul parinte afiseaza rezultatul sub forma “S-au creat <n> legaturi simbolice”.
La terminarea fiului, parintele va afisa pe ecran un mesaj de forma "Procesul fiu s-a incheiat cu codul <cod>".
Procesul fiu si procesul parinte vor rula obligatoriu in paralel.
Se vor trata cazurile de eroare pentru apelurile sistem folosite.
Functiile de biblioteca permise sunt DOAR pentru formatări (printf) si operatii asupra sirurilor de caractere.
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
#include <sys/stat.h>

struct sigaction action;
pid_t pid;
int symLinks = 0;

#define BLOCK 4096

char outFilePath[200];

void end_program(int sig)
{
    int status;
    wait(&status);
    if (!WIFEXITED(status))
    {
        perror("Error: abnormal child");
        exit(8);
    }
    printf("Procesul fiu s-a incheiat cu codul %d.\n", WEXITSTATUS(status));
    printf("S-au creat %d legaturi simbolice", symLinks);
    exit(0);
}

void realarm(int sig)
{
    char buffer[20];
    sprintf(buffer, "link_%d", symLinks + 1);
    unlink(buffer);
    if (symlink(outFilePath, buffer) < 0)
    {
        perror("Error: symlink");
        exit(4);
    }
    symLinks++;
    alarm(1);
}

void parent(char *path)
{
    strcpy(outFilePath, path);
    action.sa_handler = end_program;
    if (sigaction(SIGCHLD, &action, NULL) < 0)
    {
        perror("Error: sigaction");
        exit(3);
    }
    action.sa_handler = realarm;
    if (sigaction(SIGALRM, &action, NULL) < 0)
    {
        perror("Error: sigaction");
        exit(10);
    }
    alarm(1);
    while (1);
}

void child(int argc, char *argv[])
{
    int len;
    char *buffer;
    int file;
    if ((file = open(argv[1], O_WRONLY | O_APPEND)) < 0)
    {
        perror("Error: open");
        exit(5);
    }
    for (int i = 2; i < argc; i++)
    {
        buffer = malloc(strlen(argv[i]) * 100);
        if (buffer == NULL)
        {
            printf("Error allocating memory!\n");
            exit(6);
        }
        strcpy(buffer, "");
        for (int j = 0; j < 100; j++)
        {
            strcat(buffer, argv[i]);
        }
        len = strlen(buffer);
        if (write(file, buffer, len) < 0)
        {
            perror("Error: write");
            exit(6);
        }
        free(buffer);
        //give parent time to think, because he's slow-ish
        usleep(500000);
    }
    if (close(file) < 0)
    {
        perror("Error: close");
        exit(7);
    }
    exit(0);
}

int main(int argc, char *argv[])
{

    if (argc > 3)
    {
        struct stat myStat;
        if (lstat(argv[1], &myStat) < 0)
        {
            perror("Error: lstat");
            exit(1);
        }
        if (!S_ISREG(myStat.st_mode))
        {
            printf("Usage: ./%s <reg_file> <text1> <text2> ...\n", argv[0]);
            exit(-1);
        }
        else
        {
            if ((pid = fork()) < 0)
            {
                perror("Error: fork");
                exit(2);
            }
            if (pid == 0)
            {
                child(argc, argv);
            }
            else
            {
                parent(argv[1]);
            }
        }
    }
    else
    {

        printf("Usage: ./%s <reg_file> <text1> <text2> ...\n", argv[0]);
        exit(-1);
    }
    return 0;
}