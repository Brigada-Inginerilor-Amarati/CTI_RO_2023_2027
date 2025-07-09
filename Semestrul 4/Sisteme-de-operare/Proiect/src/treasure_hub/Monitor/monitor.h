#ifndef __MONITOR_H__
#define __MONITOR_H__

// ---------------------------------------------------------
// Includes
// ---------------------------------------------------------

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
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>

// include treasure manager
#include "../../treasure_manager/treasure_manager.h"


// ---------------------------------------------------------
// Defines
// ---------------------------------------------------------

#define TREASURE_MANAGER_EXEC  "bin/treasure_manager"
#define TREASURE_CALCULATOR_EXEC  "bin/treasure_calculator"

#define TREASURE_HUNTS_PATH "treasure_hunts"

#define BUFFER_SIZE 1024

// ---------------------------------------------------------
// global variables
// ---------------------------------------------------------

extern int output_fd_pipe;

#endif