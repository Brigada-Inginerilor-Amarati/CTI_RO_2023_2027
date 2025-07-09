#include "monitor_commands.h"

void exec_treasure_manager(char *command, char *hunt_id, char *treasure_id){
    int pipe_fd[2];

    if(pipe(pipe_fd) == -1){
        dprintf(output_fd_pipe, "Error creating pipe\n");
        return;
    }

    pid_t pid = fork();

    if(pid < 0){
        write(2, "Error forking\n", 15);
        return;
    }

    if(pid == 0){
        // close the read end of the pipe
        close(pipe_fd[0]);
        // redirect stdout to the write end of the pipe
        dup2(pipe_fd[1], 1);

        // close the write end of the pipe
        close(pipe_fd[1]);

        if(treasure_id){
            execl(TREASURE_MANAGER_EXEC, TREASURE_MANAGER_EXEC, command, hunt_id, treasure_id, NULL);
            write(2, "Error executing treasure manager\n", 34);
            exit(1);
        }
        else{
            execl(TREASURE_MANAGER_EXEC, TREASURE_MANAGER_EXEC, command, hunt_id, NULL);
            write(2, "Error executing treasure manager\n", 34);
            exit(1);
        }
    }

    // Parent process
    // close the write end of the pipe
    close(pipe_fd[1]);
    // read the output from the read end of the pipe
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer))) > 0){
        // buffer[bytes_read] = '\0';
        //dprintf(output_fd_pipe, "%s", buffer);
        // other command than dprintf
        write(output_fd_pipe, buffer, bytes_read);
    }

    if(bytes_read < 0){
        dprintf(output_fd_pipe, "Error reading from pipe\n");
    }

    // close the read end of the pipe
    close(pipe_fd[0]);

    // wait for the child process to finish
    waitpid(pid, NULL, 0);
}

void exec_calculate_score(char *hunt_id){
    int pipe_fd[2];

    if(pipe(pipe_fd) == -1){
        dprintf(output_fd_pipe, "Error creating pipe\n");
        return;
    }

    pid_t pid = fork();

    if(pid < 0){
        perror("Error forking");
        return;
    }

    if(pid == 0){
        // close the read end of the pipe
        close(pipe_fd[0]);

        // redirect stdout to the write end of the pipe
        dup2(pipe_fd[1], 1);

        // close the write end of the pipe
        close(pipe_fd[1]);
        // execute the calculator
        execl(TREASURE_CALCULATOR_EXEC, TREASURE_CALCULATOR_EXEC, hunt_id, NULL);
        write(2, "Error executing calculate score\n", 33);
        exit(1);
    }

    // Parent process

    // close the write end of the pipe
    close(pipe_fd[1]);

    // read the output from the read end of the pipe
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    while((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer))) > 0){
        // buffer[bytes_read] = '\0';
        write(output_fd_pipe, buffer, bytes_read);
    }

    if(bytes_read < 0){
        dprintf(output_fd_pipe, "Error reading from pipe\n");
    }

    // close the read end of the pipe
    close(pipe_fd[0]);

    // wait for the child process to finish
    waitpid(pid, NULL, 0);
}

void process_command(){
    char buffer[BUFFER_SIZE];

    // I use an additional file descriptor
    // so i can read the command from the terminal
    int fd = open(COMMAND_FILE_PATH, O_RDONLY);

    if(fd < 0){
        perror("Can't read command file");
        return;
    }

    int rd = read(fd, buffer, sizeof(buffer) - 1);

    close(fd);

    if(rd< 0){
        perror("Error reading command");
        return;
    }

    buffer[rd] = '\0';

    if(strcmp(buffer, "stop_monitor") == 0){
        write(1, "Monitor stop command, exit in 5s\n", 33);
        usleep(5000000);
        exit(0);
    }
    else if(strcmp(buffer, "list_hunts") == 0) {
        list_hunts(); 
    }
    else if (strncmp(buffer, "list_treasures ", 15) == 0) {
      char hunt_id[10];
      sscanf(buffer, "list_treasures %s", hunt_id);
      
      exec_treasure_manager("--list", hunt_id, NULL);
    }
    else if(strncmp(buffer, "view_treasure ", 14) == 0){
        char hunt_id[10], treasure_id[10];
        if(sscanf(buffer + 14, "%s %s", hunt_id, treasure_id) == 2){
            exec_treasure_manager("--view", hunt_id, treasure_id);
        }
        else{
            write(1, "Invalid format\n", 15);
        }
    }
    else if(strncmp(buffer, "calculate_score ", 16) == 0){
        // the logic for finding every hunt of treasure_hunts folder
        // and then exec the calculator
        // DIR *dir = opendir(TREASURE_HUNTS_PATH);

        // if(dir == NULL){
        //     write(2, "Error opening directory\n", 22);
        //     return;
        // }

        // struct dirent *entry;
        // while((entry = readdir(dir)) != NULL){
        //     if(entry->d_type == DT_DIR){
        //         // skip the . and .. directories
        //         if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
        //             char hunt_id[10];
        //             strcpy(hunt_id, entry->d_name);
        //             exec_calculate_score(hunt_id);
        //         }
        //     }
        // }

        // closedir(dir);   

        // exec with the hunt id given as argument
        char hunt_id[10];
        sscanf(buffer, "calculate_score %s", hunt_id);
        exec_calculate_score(hunt_id);
    }
    else{
        write(output_fd_pipe, "Monitor invalid command\n", 25);
    }
}