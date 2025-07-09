#ifndef __HUB_H__
#define __HUB_H__

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

// ---------------------------------------------------------
// Defines
// ---------------------------------------------------------

#define TREASURE_MANAGER_EXEC  "bin/treasure_manager"
#define TREASURE_MONITOR_EXEC  "bin/treasure_monitor"

#define BUFFER_SIZE 256

// ---------------------------------------------------------
// Structures
// ---------------------------------------------------------

typedef enum{
    INVALID_OPERATION,
    EXIT,
    START_MONITOR,
    STOP_MONITOR,
    LIST_HUNTS,
    LIST_TREASURES,
    VIEW_TREASURE,
    HELP,
    CLEAR
}Hub_Command_T;

typedef enum{
    OFF, 
    RUNNING, 
    SHUTTING_DOWN
} Status_t;

typedef struct{
    pid_t monitor_pid;
    Status_t monitor_status;
}Hub_Monitor_T;

// ---------------------------------------------------------
// functions
// ---------------------------------------------------------

int start_monitor(void);
int stop_monitor(void);
int list_hunts(void);
int list_treasures(char*);
int view_treasure(char*);



// -------------------------------------------------
// utils
// -------------------------------------------------

void handle_sigchld();
void send_command_to_monitor(const char *command);
int is_monitor_running(void);

// ---------------------------------------------------------
// extern variable
// ---------------------------------------------------------

extern Hub_Monitor_T hub_monitor;


#endif