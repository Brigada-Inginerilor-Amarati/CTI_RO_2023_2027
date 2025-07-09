#include "signal_handler.h"

// ---------------------------------------------------------
// Global Variables
// ---------------------------------------------------------

// global flag -> check if the program is running -> cleared when shutting down

extern volatile sig_atomic_t is_running;

void handle_sigusr1(int signum) {
    if (signum == SIGUSR1) {
        is_running = 1;
    }
}

void setup_signal_handlers(){
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));

    //catch shutdown signal
    sa.sa_handler = handle_sigusr1;
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGUSR1, &sa, NULL);
}
