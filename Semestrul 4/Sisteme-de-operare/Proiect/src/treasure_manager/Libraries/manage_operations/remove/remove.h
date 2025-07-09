#ifndef __REMOVE_H__
#define __REMOVE_H__

#include "../../../treasure_manager.h"
#include "../../helper_functions/utils.h"

Operation_ERROR_T remove_treasure(const char *hunt_id, const char *id);
Operation_ERROR_T remove_hunt(const char *hunt_id);

#endif