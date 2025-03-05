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

struct sigaction action;
pid_t pid;

int links;

void notify(int sig)
{
    links++;
    printf("Legatura simbolica creata.\n");
}

void finish_child()
{
    printf("%d legaturi simbolice au fost create.\n", links);
    exit(links);
}

void child()
{
    action.sa_handler = notify;
    if (sigaction(SIGUSR1, &action, NULL) < 0)
    {
        perror("Error: sigaction");
        exit(-7);
    }
    action.sa_handler = finish_child;
    if (sigaction(SIGTERM, &action, NULL) < 0)
    {
        perror("Error: sigaction");
        exit(-8);
    }
    while (1);
}

void parent(char c, int argc, char *argv[])
{
    int file, len;
    char buffer[200];
    int count = 0;
    for (int i = 2; i < argc; i++)
    {
        struct stat myStat;
        if (lstat(argv[i], &myStat) < 0)
        {
            perror("Error: lstat");
            exit(-3);
        }
        
        if (myStat.st_size > 10 && S_ISREG(myStat.st_mode))
        {
            if ((file = open(argv[i], O_RDONLY)) < 0)
            {
                perror("Error: open");
                exit(-4);
            }
            count = 0;
            while ((len = read(file, buffer, 200)) != 0)
            {
                for (int j = 0; j < len; j++)
                {
                    if (buffer[j] == c)
                    {
                        count++;
                    }
                }
            }
            if (len < 0)
            {
                perror("Error: read");
                exit(-5);
            }
            if (count != 0)
            {
                sprintf(buffer, "link_%d_%d_%d", getpid(), i, count);
                if (symlink(argv[i], buffer) < 0)
                {
                    perror("Error: symlink");
                    exit(-5);
                }
                if (kill(pid, SIGUSR1) < 0)
                {
                    perror("Error: kill");
                    exit(-6);
                }
            }
        }
    }
    if (kill(pid, SIGTERM) < 0)
    {
        perror("Error: kill");
        exit(-10);
    }

    int status;
    wait(&status);
    if (!WIFEXITED(status))
    {
            perror("Error: abnormal child");
            exit(-11);
    }
    printf("S-a incheiat procesul fiu cu pid-ul %d si codul %d.\n", pid, WEXITSTATUS(status));
}

int main(int argc, char *argv[])
{
    char c = argv[1][0];
    if (argc < 3 && ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
    {
        printf("Usage: ./%s <c> <file> <file> ...", argv[0]);
        exit(-1);
    }
    else
    {
        if ((pid = fork()) < 0)
        {
            perror("Error: fork");
            exit(-2);
        }
        else
        {
            if (pid == 0)
            {
                child();
            }
            else
            {
                parent(c, argc, argv);
            }
        }
    }
    return 0;
}