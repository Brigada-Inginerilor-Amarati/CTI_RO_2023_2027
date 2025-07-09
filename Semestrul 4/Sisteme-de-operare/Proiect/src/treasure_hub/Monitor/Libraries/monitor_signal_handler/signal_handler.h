#ifndef __SIGNAL_HANDLER_H__
#define __SIGNAL_HANDLER_H__

// ---------------------------------------------------------
// Includes
// ---------------------------------------------------------
#include "../../monitor.h"

// ---------------------------------------------------------
// Functions
// ---------------------------------------------------------

void handle_sigusr1(int signum);

void setup_signal_handlers();

#endif