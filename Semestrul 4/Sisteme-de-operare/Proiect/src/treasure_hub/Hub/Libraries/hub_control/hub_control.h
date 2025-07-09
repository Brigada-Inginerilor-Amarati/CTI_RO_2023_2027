#ifndef __HUB_CONTROL_H__
#define __HUB_CONTROL_H__

// --------------
// Includes
// --------------

#include "../../hub.h"

// -----------------
// Defines
// -----------------

#define COMMAND_FILE_PATH "monitor_command.txt"

// -----------------
// Functions
// -----------------

void send_command_to_monitor(const char *command);

int is_monitor_running();

int start_monitor();

int stop_monitor();

int list_hunts();

int list_treasures(char* input);

int view_treasure(char* input);

int calculate_score();

int calculate_score2(char* input);

#endif