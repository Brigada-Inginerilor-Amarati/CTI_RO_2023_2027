#include "monitor.h"

// ---------------------------------------------------------
// Global state
// ---------------------------------------------------------

// this means that the program is running -> 1 
volatile sig_atomic_t is_running = 1;

// main loop

void monitor_loop(){
    char command[BUFFER_SIZE];

    // this is used to check if the program is running
    while (is_running) {
        // clear the line
        write(1, "\r", 1);  // stdout file

        // print the prompt
        write(1, "monitor> ", 9);

        // read the command
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        // execute the command
        execute_treasure_manager(command);
    }
    
}

int main(void){
    char message[BUFFER_SIZE];

    setup_signal_handlers();

    snprintf(message, sizeof(message), "Monitor started with pid %d\n", getpid());
    write(1, message, strlen(message)); // stdout file

    //main loop
    monitor_loop();

    sleep(5);

    snprintf(message, sizeof(message), "Monitor terminated with pid %d\n", getpid());
    write(1, message, strlen(message)); // stdout file
    return 0;
}