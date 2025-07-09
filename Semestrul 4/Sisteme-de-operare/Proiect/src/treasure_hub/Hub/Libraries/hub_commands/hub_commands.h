#ifndef __HUB_COMMANDS_H__
#define __HUB_COMMANDS_H__

// ------------------------
// Includes
// ------------------------

#include "../../hub.h"
#include "../hub_control/hub_control.h"

// ------------------------
// Functions
// ------------------------

void print_help();

Hub_Command_T get_command_type(char *input);

void execute_command(Hub_Command_T command, char *input);

#endif