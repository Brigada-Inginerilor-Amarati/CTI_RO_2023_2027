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

#define BUFF_LEN 4096

struct sigaction action;
pid_t pid;

int main(int argc, char *argv[])
{
    int len;
    int file;
    char buffer[BUFF_LEN];
    if ((file = open(argv[3], O_RDWR)) < 0)
    {
        perror("Error: open");
        exit(1);
    }

    while ((len = read(file, buffer, BUFF_LEN)) != 0)
    {
        for (int i = 0; i < len; i++)
        {
            if (buffer[i] == argv[1][0])
            {
                buffer[i] = argv[2][0];
            }
        }
        lseek(file, -len, SEEK_CUR);
        if (write(file, buffer, len) < 0)
        {
            {
                perror("Error: write");
                exit(1);
            }
        }
    }

    return 0;
}