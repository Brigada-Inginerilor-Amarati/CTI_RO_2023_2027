#ifndef __SIGNAL_HANDLER_H__
#define __SIGNAL_HANDLER_H__

// --------------
// Includes
// --------------

#include "../../hub.h"

// --------------
//  Functions
// --------------

void on_sigchld(int signo);

void handle_sigchld();



#endif