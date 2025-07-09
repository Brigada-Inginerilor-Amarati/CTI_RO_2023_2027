// ---------------------
// Includes
// ---------------------

#include "monitor.h"
// this is for the monitor signal
#include "Libraries/monitor_signal_handler/signal_handler.h"
// this is for the monitor commands
#include "Libraries/monitor_commands/monitor_commands.h"

// ---------------------------------------------------------
// the HUB will fork the monitor 
// ---------------------------------------------------------

//  ---------------------------------------------------------
//  Global State
//  ---------------------------------------------------------

volatile sig_atomic_t is_running = 1;

int main(int argc, char **argv) {
    // we set the output file 
    if(argc >= 2){
        output_fd_pipe = atoi(argv[1]);
    }

    char message[BUFFER_SIZE];

    // setup signal handlers
    setup_signal_handlers();

    // start the monitor loop
    snprintf(message, sizeof(message), "Monitor started. Type commands to execute the treasure manager.\n");
    
    write(1, message, strlen(message));

    while (1) {
        pause();

	    if (is_running) {
	        process_command();
	        is_running = 0;
	    }
    }

    return 0;
}