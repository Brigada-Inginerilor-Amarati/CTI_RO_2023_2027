#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

struct sigaction process_action;
double value;
int rank, print_times, chr_changes = 1, index_chr = 0;
long nr_of_chars[3];
char chr = '*';
pid_t pid;

// CHILD
void print_current_term(int sig)
{
    printf("a[%d] = %lf\n", rank, value);
    if (print_times < 1)
        print_times++;
    else
        exit(4);
}

void process_child(int initVal, int ratio)
{
    value = initVal;
    while (1)
    {
        value += (1 / (double)ratio);
        rank++;
    }
}

//PARENT
void process_parent()
{
    alarm(1);
    while (1)
    {
        nr_of_chars[index_chr]++;
        //printf("%c", chr);
    }
}

void reprogram_alarm_change_char(int sig)
{
    printf("%c x %ld\n", chr, nr_of_chars[index_chr]);
    index_chr++;
    if (chr_changes < 3)
    {
        chr += chr_changes;
        chr_changes++;
    }
    if (kill(pid, SIGUSR1) < 0)
    {
        printf("Error sending SIGUSR1 to child\n");
        exit(2);
    }
    alarm(1);
}

void end_parent(int sig)
{
    int status;
    if (wait(&status) < 0)
    {
        printf("Error waiting child\n");
        exit(2);
    }
    printf("\nChild ended with code %d\n", WEXITSTATUS(status));
    printf("Parent ends.\n");
    exit(0);
}

int main(int argc, char *argv[])
{
    memset(&process_action, 0x00, sizeof(struct sigaction));
    if (argc != 3)
    {
        printf("Usage: ./%s <value> <ratio>", argv[0]);
        exit(0);
    }
    else
    {
        if ((pid = fork()) < 0)
        {
            printf("Error creating child process.\n");
            exit(1);
        }

        if (pid == 0)
        {
            process_action.sa_handler = print_current_term;
            if (sigaction(SIGUSR1, &process_action, NULL) < 0)
            {
                perror("Process a SIGUSR1 sigaction!");
                exit(-1);
            }
            process_child(atoi(argv[1]), atoi(argv[2]));
            exit(0);
        }
        else
        {
            process_action.sa_handler = reprogram_alarm_change_char;
            if (sigaction(SIGALRM, &process_action, NULL) < 0)
            {
                perror("Process a SIGALRM sigaction!");
                exit(-1);
            }
            process_action.sa_handler = end_parent;
            if (sigaction(SIGCHLD, &process_action, NULL) < 0)
            {
                perror("Process a SIGALRM sigaction!");
                exit(-1);
            }
            process_parent();
        }
    }

    return 0;
}