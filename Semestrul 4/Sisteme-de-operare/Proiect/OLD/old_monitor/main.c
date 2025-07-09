#include "monitor.h"

// ---------------------------------------------------------
// the HUB will fork the monitor 
// ---------------------------------------------------------

//  ---------------------------------------------------------
//  Global State
//  ---------------------------------------------------------

volatile sig_atomic_t is_running = 1;

int main(void){
    char message[BUFFER_SIZE];

    // setup signal handlers
    setup_signal_handlers();

    // start the monitor loop
    snprintf(message, sizeof(message), "Monitor started. Type commands to execute the treasure manager.\n");
    
    write(STDOUT_FILENO, message, strlen(message));

    while (1) {
        pause();

	if (is_running) {
	  process_command();
	  is_running = 0;
	}
    }

    return 0;
}