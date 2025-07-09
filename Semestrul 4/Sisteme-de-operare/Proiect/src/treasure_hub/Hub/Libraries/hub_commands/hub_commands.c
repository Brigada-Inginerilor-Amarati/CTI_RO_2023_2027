#include "hub_commands.h"

void print_help(){
    write(1, "Commands:\n", 10);
    write(1, "start_monitor\n", 14);
    write(1, "stop_monitor\n", 13);
    write(1, "list_hunts\n", 12);
    write(1, "list_treasures\n", 16);
    write(1, "view_treasure\n", 14);
    write(1, "calculate_score\n", 16);
    write(1, "help\n", 6);
    write(1, "clear\n", 7);
    write(1, "exit\n", 6);
}

Hub_Command_T get_command_type(char *input){
    if(strcmp(input, "start_monitor") == 0){
        return START_MONITOR;
    } 
    else if(strcmp(input, "stop_monitor") == 0){
        return STOP_MONITOR;
    } 
    else if(strcmp(input, "list_hunts") == 0){
        return LIST_HUNTS;
    } 
    else if(strncmp(input, "list_treasures ", 15) == 0){
        return LIST_TREASURES;
    } 
    else if(strncmp(input, "view_treasure ", 14) == 0){
        return VIEW_TREASURE_FROM_HUNT;
    } 
    else if(strcmp(input, "help") == 0){
        return HELP_COMMAND;
    } 
    else if(strcmp(input, "clear") == 0){
        return CLEAR;
    } 
    else if(strcmp(input, "exit") == 0){
        return EXIT;
    }
    else if(strncmp(input, "calculate_score ", 16) == 0){
        return CALCULATE_SCORE;
    }
    else {
        return INVALID_OPERATION_GAVE;
    }
}

void execute_command(Hub_Command_T command, char *input){
    switch(command){
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
            list_treasures(input);
            break;
        case VIEW_TREASURE_FROM_HUNT:
            view_treasure(input);
            break;
        case HELP_COMMAND:
            print_help();
            break;
        case CLEAR:
            system("clear");
            break;
        case EXIT:
            if (is_monitor_running()) {
                    write(1, "Please stop the monitor before exiting.\n", 40);
                }
            else{
                exit(0);
            }
        case CALCULATE_SCORE:
            calculate_score2(input);
            break;
        default:
            printf("Invalid command. Type 'help' for a list of commands.\n");
            break;
        
    }
}
