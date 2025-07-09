#include "hub.h"

// ---------------------------------------------------------
// INITIAL STATE
// ---------------------------------------------------------

Hub_Monitor_T hub_monitor = {-1, OFF};

void send_command_to_monitor(const char *command) {
    int fd = open("monitor_command.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open command file");
        return;
    }

    write(fd, command, strlen(command));
    close(fd);

    kill(hub_monitor.monitor_pid, SIGUSR1);
}

int is_monitor_running(){
    if(hub_monitor.monitor_pid > 0 && hub_monitor.monitor_status == RUNNING){
        return 1;
    }
    return 0;
}

// 0 -> fail 1 -> success
int start_monitor() {
    if (is_monitor_running()) {
        write(1, "Monitor is already running\n", 26);
        return 0;
    }

    hub_monitor.monitor_pid = fork();
    if (hub_monitor.monitor_pid < 0) {
        write(1, "Failed to fork monitor process\n", 31);
        return 0;
    }

    if (hub_monitor.monitor_pid == 0) {
        // Child process - the monitor
        execl(TREASURE_MONITOR_EXEC, TREASURE_MONITOR_EXEC, NULL);
        perror("execl failed");
        exit(EXIT_FAILURE);
    }

    //hub_monitor.monitor_pid = pid;
    hub_monitor.monitor_status = RUNNING;
    return 1;
}


// 0 -> fail 1 -> success
int stop_monitor() {
    if (!is_monitor_running()) {
        write(1, "Monitor is not running.\n", 24);
        return 0;
    }

    send_command_to_monitor("stop");

    /*pid_t old_pid = hub_monitor.monitor_pid;
    hub_monitor.monitor_status = SHUTTING_DOWN;
    
    if (kill(old_pid, SIGTERM) == -1) {
        perror("Failed to send SIGTERM");
        return 0;
    }
    
    // Wait for process to terminate
    int status;
    pid_t result = waitpid(old_pid, &status, WNOHANG);
    
    if (result == -1) {
        perror("waitpid failed");
        return 0;
    }
    
    if (result == old_pid) {    
        hub_monitor.monitor_pid = -1;
        hub_monitor.monitor_status = OFF;
        write(1, "Monitor stopped successfully.\n", 29);
        return 1;
	}*/
    
    write(1, "Monitor is shutting down...\n", 28);
    return 1;
}

int list_hunts(){
    if (!is_monitor_running()) {
        write(1, "Monitor is not running.\n", 24);
        return 0;
    }

    send_command_to_monitor("list_hunts");
    return 1;
}

int list_treasures(char *input){
    if (!is_monitor_running()) {
        write(1, "Monitor is not running.\n", 24);
        return 0;
    }

    char *hunt_id = input + 15;
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "list_treasures %s", hunt_id);
    send_command_to_monitor(command);
    return 1;
}

int view_treasure(char *input){
    if (!is_monitor_running()) {
        write(1, "Monitor is not running.\n", 24);
        return 0;
    }

    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "%s", input);
    send_command_to_monitor(command);
    return 1;
}


void on_sigchld(int signo){
    int status;
    pid_t pid = wait(&status);
    if (pid == hub_monitor.monitor_pid) {
      printf("Monitor exited with status %d\n", WEXITSTATUS(status));
      hub_monitor.monitor_status = OFF;
    }
}

void handle_sigchld(){
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = on_sigchld;
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, NULL);
}