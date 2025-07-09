#ifndef __MONITOR_H__
#define __MONITOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <time.h>

// ---------------------------------------------------------
// Defines
// ---------------------------------------------------------

#define TREASURE_MANAGER_EXEC  "bin/treasure_manager"


#define BUFFER_SIZE 256
// ---------------------------------------------------------
// Global Variables
// ---------------------------------------------------------

// this is used to check if the program is running

extern volatile sig_atomic_t is_running;

// -----------------------------------------------------------
// Functions
// -----------------------------------------------------------

// this executes the treasure manager with the given command string
void execute_treasure_manager(const char *command);

// this is used for signal setup 
void setup_signal_handlers();

#endif