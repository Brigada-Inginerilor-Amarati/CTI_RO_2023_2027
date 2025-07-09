#include "hub_control.h"

// ---------------------------------------------------------
// INITIAL STATE
// ---------------------------------------------------------

Hub_Monitor_T hub_monitor = {-1, OFF};

int fd_for_pipe = -1;

void send_command_to_monitor(const char *command){
    int fd = open(COMMAND_FILE_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    //perror("here\n");
    if (fd < 0) {
        perror("open command file");
        return;
    }

    write(fd, command, strlen(command));
    // write(fd, "\n", 1); // Add a newline to indicate end of command
    close(fd);

    kill(hub_monitor.monitor_pid, SIGUSR1);

    char buffer[BUFFER_SIZE];

    ssize_t len = read(fd_for_pipe, buffer, sizeof(buffer) - 1);

    if (len < 0) {
        write(1, "Failed to read from pipe\n", 24);
        return;
    }

    if(len > 0) {
        buffer[len] = '\0';
        //write(1, buffer, len);
        write(1, buffer, strlen(buffer));
        
    } else {
        write(1, "No response from monitor\n", 25);
    }
}

int is_monitor_running(void){
    if (hub_monitor.monitor_pid > 0 && hub_monitor.monitor_status == RUNNING) {
        return 1;
    }

    return 0;
}

// 0 -> fail 1 -> success
int start_monitor(void){
    if (is_monitor_running()) {
        write(1, "Monitor is already running\n", 26);
        return 0;
    }

    // Create a pipe for communication with the monitor
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        write(1, "Failed to create pipe\n", 22);
        return 0;
    }



    hub_monitor.monitor_pid = fork();
    if (hub_monitor.monitor_pid < 0) {
        write(1, "Failed to fork monitor process\n", 31);
        return 0;
    }

    if (hub_monitor.monitor_pid == 0) {
        // Child process - the monitor
        close(pipefd[0]); // Close the read end of the pipe

        char write_fd[BUFFER_SIZE];
        sprintf(write_fd, "%d", pipefd[1]);

        execl(TREASURE_MONITOR_EXEC, TREASURE_MONITOR_EXEC, write_fd, NULL);

        // this was modified for the phase 3
        //execl(TREASURE_MONITOR_EXEC, TREASURE_MONITOR_EXEC, NULL);
        perror("execl failed");
        exit(EXIT_FAILURE);
    }

    // Parent process - the hub
    // store the read end of the pipe(global variable fd_for_pipe)
    fd_for_pipe = pipefd[0];
    // close the write end
    close(pipefd[1]);

    hub_monitor.monitor_status = RUNNING;
    return 1;

}

int stop_monitor(void){
    if (!is_monitor_running()) {
        write(1, "Monitor is not running.\n", 24);
        return 0;
    }

    //send_command_to_monitor("stop_monitor");

    kill(hub_monitor.monitor_pid, SIGTERM);

    waitpid(hub_monitor.monitor_pid, NULL, 0);

    hub_monitor.monitor_pid = -1;
    hub_monitor.monitor_status = OFF;
    write(1, "Monitor stopped.\n", 17);


    //write(1, "Monitor is shutting down...\n", 28);
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

int list_treasures(char* input){
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

int view_treasure(char* input){
    if (!is_monitor_running()) {
        write(1, "Monitor is not running.\n", 24);
        return 0;
    }

    char command[BUFFER_SIZE];
    
    snprintf(command, sizeof(command), "%s", input);
    send_command_to_monitor(command);

    return 1;
}

int calculate_score(){
    if (!is_monitor_running()) {
        write(1, "Monitor is not running.\n", 24);
        return 0;
    }

    send_command_to_monitor("calculate_score");
    return 1;
}

int calculate_score2(char* input){
    if (!is_monitor_running()) {
        write(1, "Monitor is not running.\n", 24);
        return 0;
    }

    char *hunt_id = input + 16;
    char command[BUFFER_SIZE];

    snprintf(command, sizeof(command), "calculate_score %s", hunt_id);

    send_command_to_monitor(command);
    //send_command_to_monitor("calculate_score");
    return 1;
}