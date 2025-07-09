#include "hub.h"



// ---------------------------------------------------------
// functions
// ---------------------------------------------------------

void print_help(){
    write(1, "Commands:\n", 10);
    write(1, "start_monitor\n", 14);
    write(1, "stop_monitor\n", 13);
    write(1, "list_hunts\n", 12);
    write(1, "list_treasures\n", 16);
    write(1, "view_treasure\n", 14);
    write(1, "help\n", 6);
    write(1, "clear\n", 7);
    write(1, "exit\n", 6);
}

static Hub_Command_T get_command(char *command){
    if(strcmp(command, "start_monitor") == 0){
        return START_MONITOR;
    } 
    else if(strcmp(command, "stop_monitor") == 0){
        return STOP_MONITOR;
    } 
    else if(strcmp(command, "list_hunts") == 0){
        return LIST_HUNTS;
    } 
    else if(strncmp(command, "list_treasures ", 15) == 0){
        return LIST_TREASURES;
    } 
    else if(strncmp(command, "view_treasure ", 14) == 0){
        return VIEW_TREASURE;
    } 
    else if(strcmp(command, "help") == 0){
        return HELP;
    } 
    else if(strcmp(command, "clear") == 0){
        return CLEAR;
    } 
    else if(strcmp(command, "exit") == 0){
        return EXIT;
    }
    return INVALID_OPERATION;
}


int main(void){
    char command[BUFFER_SIZE];
    Hub_Command_T command_type;

    handle_sigchld();  // monitor process cleanup

    while (1) {
        write(1, "> ", 2);

        ssize_t bytes = read(0, command, sizeof(command) - 1);
        if (bytes <= 0) break;

        command[bytes - 1] = '\0';  // remove newline
        command_type = get_command(command);

        if (hub_monitor.monitor_status == SHUTTING_DOWN) {
            write(1, "Monitor is shutting down. Please wait...\n", 42);
            continue;
        }

        switch (command_type) {
            case START_MONITOR:
                start_monitor();
                break;
            case STOP_MONITOR:
                stop_monitor();
                break;
            case LIST_HUNTS:
                list_hunts();
                break;
            case LIST_TREASURES:
                list_treasures(command);
                break;
            case VIEW_TREASURE:
                view_treasure(command);
                break;
            case HELP:
                print_help();
                break;
            case CLEAR:
                write(1, "\033[H\033[J", 6);  // ANSI clear screen
                break;
            case EXIT:
                if (is_monitor_running()) {
                    write(1, "Error: monitor is still running. Stop it first.\n", 48);
                } else {
                    return 0;
                }
                break;
            case INVALID_OPERATION:
                write(1, "Invalid command. Type 'help' for options.\n", 42);
                break;
        }
    }

    return 0;
}