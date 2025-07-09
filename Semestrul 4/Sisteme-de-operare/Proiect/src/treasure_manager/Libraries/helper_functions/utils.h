#ifndef __UTILS_H__
#define __UTILS_H__

#include "../../treasure_manager.h"

// ---------------------------------------
// treasure create
// ---------------------------------------

Treasure_T *create_treasure();

// ---------------------------------------
// DIR
// ---------------------------------------

Operation_ERROR_T DIR_exists(const char *dir_path);
Operation_ERROR_T DIR_create(const char *dir_path);

// ---------------------------------------
// FILE
// ---------------------------------------

int FILE_create(const char *file_path);
int symlink_create(const char *hunt_id);

#endif