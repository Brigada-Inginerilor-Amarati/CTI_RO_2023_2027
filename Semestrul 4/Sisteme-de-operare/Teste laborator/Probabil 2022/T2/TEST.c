/*
Sa se implementeze:
A) un shell script care se apeleaza sub forma bash script <file>
Script-ul verifica faptul ca a primit un argument; in caz contrar, va afisa un mesaj de utilizare.
Se citesc siruri de caractere de la tastatură (stdin) până la la EOF (Ctrl+D) si fiecare sir de caractere citit se scrie in <file>. La final se va afisa pe ecran continutul <file>.
B) un program C, folosind apeluri sistem si functii de biblioteca care se apeleaza sub forma ./executabil <file_in> <file_out>, unde argumentele sunt cai catre fisiere (NU trebuie sa verificati daca sunt fisiere).
Programul verifica faptul ca a primit un argument; in caz contrar, afiseaza un mesaj de eroare ce indica utilizarea corecta.
Procesul parinte creeaza trei procese fiu. Primul proces fiu lanseaza in executie OBLIGATORIU o comanda pentru a trimite continutul <file_in> catre parinte. 
Parintele trimite doar caracterele care nu reprezinta spatii albe catre al doilea fiu. Pentru fiecare spatiu alb gasit parintele trimite semnalul SIGUSR1 catre fiul al treilea. 
Al doilea proces fiu primeste informatia de la parinte si lanseaza in executie script-ul de la punctul (A) cu <file_out> ca argument. 
Al treilea proces fiu numara de care ori a primit semnalul si afiseaza contorul cand parintele termina de citit fisierul.
La terminarea fiecarui proces fiu, parintele afiseaza un mesaj de forma: 
" Procesul fiu cu PID-ul <PID> s-a incheiat cu codul <cod>". 
Procesele fiu si procesul parinte vor rula obligatoriu in paralel.
Se vor trata cazurile de eroare pentru apelurile sistem folosite.
Functiile de biblioteca permise sunt DOAR pentru formatări (printf, sprintf) şi operatii asupra sirurilor de caractere.
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
pid_t pid1, pid2, pid3;
int p1[2], p2[2];
char buff[100];
int childs = 3, times_child3;

void child1(char *input_path)
{
    close(p2[0]);
    close(p2[1]);
    close(p1[0]);
    dup2(p1[1],1);
    close(p1[1]);
    execlp("cat", "cat", input_path, NULL);
    perror("Error: child1");
    exit(-10);
}

void child2(char *output_path)
{
    close(p1[0]);
    close(p1[1]);
    close(p2[1]);
    dup2(p2[0],0);
    close(p2[0]);
    execlp("bash", "bash", "TEST.sh", output_path, NULL);
    perror("Error: child2");
    exit(-20);
}

void child3_sigusr1_handler(int sig)
{
    times_child3++;
}

void child3_sigterm_handler(int sig)
{
    printf("I received the SIGUSR1 signal %d times!\n", times_child3);
    exit(0);
}

void child3()
{
    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]);
    action.sa_handler = child3_sigusr1_handler;
    if (sigaction(SIGUSR1, &action, NULL) < 0)
    {
        perror("Error: sigaction");
        exit(6);
    }
    action.sa_handler = child3_sigterm_handler;
    if (sigaction(SIGTERM, &action, NULL) < 0)
    {
        perror("Error: sigaction");
        exit(6);
    }
    while (1)
    {
    }
}

void parent_handler(int sig)
{
    int status;
    int pid = wait(&status);
    if (!WIFEXITED(status))
    {
        perror("Error: abnormal child");
        exit(8);
    }
    printf("Procesul cu PID-ul %d s-a incheiat cu codul %d.\n", pid, WEXITSTATUS(status));
    childs--;
    if (childs == 0)
    {
        printf("The boss (parent) left the room!\n");
        exit(0);
    }
}

void parent()
{
    action.sa_handler = parent_handler;
    if (sigaction(SIGCHLD, &action, NULL) < 0)
    {
        perror("Error: sigaction");
        exit(6);
    }
    
    close(p1[1]);
    close(p2[0]);
    char one[1];
    int s = 0;
    while ((s = read(p1[0], buff, M_BUFF)))
    {
        for (int i = 0; i < M_BUFF; i++)
        {
            if (buff[i] == ' ')
            {
                if (kill(pid3, SIGUSR1) < 0)
                {
                    perror("Error: kill");
                    exit(5);
                }
            }
            else
            {
                one[0] = buff[i];
                if (write(p2[1], one, 1) < 0)
                {
                    perror("Error: write");
                    exit(5);
                }
            }
        }
    }
    close(p1[0]);
    close(p2[1]);
    if (s < 0)
    {
        perror("Error: read");
        exit(4);
    }
    if (kill(pid3, SIGTERM) < 0)
    {
        perror("Error: kill");
        exit(5);
    }
    while (1)
    {
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <file_in> <file_out>", argv[0]);
        exit(-1);
    }
    else
    {
        if (pipe(p1) < 0)
        {
            perror("Error: fork");
            exit(2);
        }

        if (pipe(p2) < 0)
        {
            perror("Error: fork");
            exit(2);
        }

        if ((pid1 = fork()) < 0)
        {
            perror("Error: fork");
            exit(1);
        }

        if (pid1 == 0)
        {
            child1(argv[1]);
        }

        if ((pid2 = fork()) < 0)
        {
            perror("Error: fork");
            exit(1);
        }

        if (pid2 == 0)
        {
            child2(argv[2]);
        }

        if ((pid3 = fork()) < 0)
        {
            perror("Error: fork");
            exit(1);
        }

        if (pid3 == 0)
        {
            child3();
        }

        parent();
    }
    return 0;
}