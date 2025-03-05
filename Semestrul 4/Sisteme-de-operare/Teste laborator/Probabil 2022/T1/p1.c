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
int outFile;
char buffer[] = "Am primit semnalul SIGUSR1\n";

void end_child(int sig)
{
    exit(6);
}

void child_process()
{
    action.sa_handler = end_child;
    if (sigaction(SIGUSR2, &action, NULL) < 0)
    {
        perror("error: sigaction");
        exit(-4);
    }
    while (1)
    {
        //sleep(1);
        if (kill(getppid(), SIGUSR1) < 0)
        {
            perror("error: kill");
            exit(-4);
        }
    }
}

void write_in_file(int sig)
{

    if (write(outFile, buffer, strlen(buffer)) < 0)
    {
        perror("error: write");
        exit(-6);
    }
}

void parent_process(char *filePath, char *dir, pid_t pid)
{
    action.sa_handler = write_in_file;
    if (sigaction(SIGUSR1, &action, NULL) < 0)
    {
        perror("error: sigaction");
        exit(-4);
    }


    DIR *directory;
    struct stat fileStat;
    if ((outFile = open(filePath, O_WRONLY)) < 0)
    {
        perror("error: open");
        exit(-5);
    }

    if ((directory = opendir(dir)) == NULL)
    {
        perror("error: opendir");
        exit(-5);
    }

    char path[500];
    struct dirent *file;
    while ((file = readdir(directory)) != NULL)
    {
        if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0)
            continue;


        strcpy(path, dir);
        strcat(path, "/");
        strcat(path, file->d_name);
        if (lstat(path, &fileStat) < 0)
        {
            perror("error: lstat");
            exit(-5);
        }
        if (S_ISDIR(fileStat.st_mode))
        {
            printf("%s este director.\n", file->d_name);
        }
    }
    if (closedir(directory) < 0)
    {
        perror("error: closedir");
        exit(-5);
    }
    if (kill(pid, SIGUSR2) < 0)
    {
        perror("error: kill");
        exit(-5);
    }


    int status;
    wait(&status);
    if (!WIFEXITED(status))
    {
        perror("error: abnormal child");
        exit(-5);
    }
    printf("Procesul cu PID-ul %d s-a incheiat cu codul %d.", pid, WEXITSTATUS(status));
    if (close(outFile) < 0)
    {
        perror("error: close");
        exit(-5);
    }
}

int main(int argc, char *argv[])
{
    pid_t pid;
    if (argc != 3)
    {
        printf("Usage: ./%s <file> <directory>", argv[0]);
        exit(-1);
    }
    else
    {
        struct stat fileStat, dirStat;
        if (lstat(argv[1], &fileStat) < 0)
        {
            perror("error: lstat");
            exit(-2);
        }
        if (lstat(argv[2], &dirStat) < 0)
        {
            perror("error: lstat");
            exit(-2);
        }
        if (!S_ISREG(fileStat.st_mode) || !S_ISDIR(dirStat.st_mode))
        {
            printf("Usage: ./%s <file> <directory>", argv[0]);
            exit(-1);
        }
        else
        {
            if ((pid = fork()) < 0)
            {
                perror("error: fork");
                exit(-3);
            }
            if (pid == 0)
            {
                child_process();
            }
            else
            {
                parent_process(argv[1], argv[2], pid);
            }
        }
    }

    return 0;
}