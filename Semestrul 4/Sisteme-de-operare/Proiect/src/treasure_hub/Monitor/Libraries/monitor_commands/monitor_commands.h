#ifndef __MONITOR_COMMANDS_H__
#define __MONITOR_COMMANDS_H__

// --------------------------
// Includes
// --------------------------

#include "../../monitor.h"
#include "../list_hunts/list_hunts.h"

// --------------------------
// Defines
// --------------------------

#define COMMAND_FILE_PATH "monitor_command.txt"

// --------------------------
// Functions
// --------------------------

void exec_treasure_manager(char *command, char *hunt_id, char *treasure_id);

void exec_calculate_score(char *hunt_id);

void process_command();

#endif