#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <signal.h>

int times = 0;
int childs = 0;

void child(char *file, char *newDir, int sig)
{
    struct sigaction action;
    memset(&action, 0x00, sizeof(struct sigaction));
    if (sigaction(sig, &action, NULL) < 0)
    {
        perror("Error sigaction!");
        exit(2);
    }

    if (sigaction(SIGCHLD, &action, NULL) < 0)
    {
        perror("Error sigaction!");
        exit(2);
    }

    DIR *dr;
    char buffer[50];
    int i = 0;
    int bytes = 0;
    if ((dr = opendir(newDir)) == NULL)
    {
        perror("Error dir!");
        exit(2);
    }

    char newPath[2000];
    strcpy(newPath, newDir);
    strcat(newPath, "/");
    strcat(newPath, file);
    int fileI = open(file, O_RDONLY);
    int fileO = open(newPath, O_CREAT | O_RDWR, S_IRWXU);
     if (fileO < 0)
    {
        perror("Error file!");
        exit(4);
    }

    while (read(fileI, buffer + i, 1))
    {
        bytes++;
        if (buffer[i] == ' ')
        {
            strcat(buffer, "\n\0");
            write(fileO, buffer, strlen(buffer));
            i = 0;
            strcpy(buffer, "");
            if (kill(getppid(), sig) < 0)
            {
                perror("Error kill!");
                exit(5);
            }
        }
        else
        {
            i++;
        }
    }
    exit(bytes);
}

void countSig(int sig)
{
    times++;
}

void finishChld(int sig)
{


}


int main(int argc, char *argv[])
{
    pid_t pid;
    if (argc != 4)
    {
        printf("Usage: ./%s <dir1> <dir2> <sig>", argv[0]);
        exit(1);
    }
    else
    {
        struct sigaction action;
        memset(&action, 0x00, sizeof(struct sigaction));
        action.sa_handler = countSig;
        if (sigaction(atoi(argv[3]), &action, NULL) < 0)
        {
            perror("Error sigaction!");
            exit(2);
        }

        action.sa_handler = finishChld;
        if (sigaction(SIGCHLD, &action, NULL) < 0)
        {
            perror("Error sigaction!");
            exit(2);
        }

        DIR *dr;
        if ((dr = opendir(argv[1])) == NULL)
        {
            perror("Error dir!");
            exit(2);
        }
        else
        {
            struct dirent *file;
            while ((file = readdir(dr)) != NULL)
            {
                if(file->d_name[0] == '.')
                    continue;
                struct stat fileStat;
                if (stat(file->d_name, &fileStat) == 0)
                {
                    if (fileStat.st_mode & S_IRUSR & S_IWUSR)
                    {
                        if ((pid = fork()) < 0)
                        {
                            perror("Error fork!");
                            exit(3);
                        }
                        else
                        {
                            if (pid == 0)
                                child(file->d_name, argv[2], atoi(argv[3]));
                        }
                    }
                }
            }
        }
        closedir(dr);
    }
}