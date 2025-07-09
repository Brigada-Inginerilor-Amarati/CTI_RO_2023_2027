#include "hub.h"

#include "Libraries/hub_commands/hub_commands.h"
#include "Libraries/hub_signal_handler/signal_handler.h"
#include "../Calculate_Score/calculate_score.h"

int main(void){
    char command[BUFFER_SIZE];
    Hub_Command_T command_type;

    handle_sigchld();  // monitor process

    while(1){
        // Prompt for user input
        write(1, "> ", 2);

        ssize_t bytes = read(0, command, sizeof(command) - 1);
        if (bytes <= 0) break;

        // Null-terminate the command string
        command[bytes] = '\0';
        // Remove trailing newline character
        if (command[bytes - 1] == '\n') {
            command[bytes - 1] = '\0';
        }

        // Get the command type
        command_type = get_command_type(command);

        if(hub_monitor.monitor_status == SHUTTING_DOWN){
            write(1, "Monitor is shutting down. Please wait...\n", 42);
            continue;
        }

        // Execute the command
        execute_command(command_type, command);
    }

    return 0;
}