#include "monitor.h"

void execute_treasure_manager(const char* command){
    char message[BUFFER_SIZE];

    // fork and execute 
    pid_t pid = fork();

    if(pid < 0){
        // clear the line
        write(1, "\r", 1);  // stdout file 

        // print the error message
        snprintf(message, sizeof(message), "Error: %s\n", strerror(errno));

        write(2, message, strlen(message)); // stderr file

        return;
    }

    if(pid == 0){
        // in the child process, we ll execute the treasure manager

        execlp(TREASURE_MANAGER_EXEC, TREASURE_MANAGER_EXEC, (char*) NULL);

        // if execlp fails, we ll print the error message

        write(1, "\r", 1);  // stdout file

        snprintf(message, sizeof(message), "Error: %s\n", strerror(errno));

        write(2, message, strlen(message)); // stderr file

        exit(EXIT_FAILURE);
    } 

    // the parent process will wait for the child to finish
    int status; 

    waitpid(pid, &status, WNOHANG);

    // refresh the screen
    kill(getpid(), SIGUSR1);
}

// monitor shutdown 

void handle_sig(int signum){
    // this is used for the shutdown signal - > go to previous line
    write(1, "\r", 1);  // stdout file

    char message[BUFFER_SIZE];
    snprintf(message, sizeof(message), "Treasure manager terminated with status %d\n", signum);
    write(1, message, strlen(message)); // stdout file

    // this means that the program is running -> 0
    is_running = 0;
}

void setup_signal_handlers(){
    struct sigaction sa_term;

    memset(&sa_term, 0, sizeof(sa_term));

    struct sigaction sa_child;

    memset(&sa_child, 0, sizeof(sa_child));

    sa_term.sa_handler = handle_sig;

    if (sigaction(SIGTERM, &sa_term, NULL) == -1) {
        perror("sigaction(SIGTERM) failed");
        exit(EXIT_FAILURE);
    }
    
    sigaction(SIGINT, &sa_term, NULL);// request to interrupt the process
    sigaction(SIGHUP, &sa_term, NULL);// hang up signal

    sa_child.sa_handler = SIG_IGN; // ignore the child process signal
    sa_child.sa_flags = SA_NOCLDSTOP | SA_RESTART; // ignore the child process signal
    sigaction(SIGCHLD, &sa_child, NULL);// child process terminated

}