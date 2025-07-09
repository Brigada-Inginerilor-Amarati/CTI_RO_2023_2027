#ifndef __TREASURE_H__
#define __TREASURE_H__


#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>

#define MAX_ID_LEN 16
#define MAX_USERNAME_LEN 32
#define MAX_CLUETEXT_LEN 128
#define MAX_PATH_LEN_DIR 256
#define MAX_PATH_LEN_FILE 512

#define TREASURE_DIR "treasure_hunts"
#define TREASURE_FILE "treasure.bin"
#define TREASURE_LOG "logged_hunt.txt"
#define TREASURE_SYMLINK "logged_hunt"    

// GPS Coordinate struct
typedef struct Coordonata{
    float latitude;
    float longitude;
}Coordonata_T;

// the struct for the first requirement
typedef struct Treasure{
    char id[MAX_ID_LEN];
    char userName[MAX_ID_LEN];
    Coordonata_T GPSCoordinate;
    char clueText[MAX_CLUETEXT_LEN];
    int value;
}Treasure_T;

// helper functions

Treasure_T *create_treasure();
int DIR_exists(const char *dir_path);
int DIR_create(const char *dir_path);

int FILE_create(const char *file_path);

int symlink_create(const char *hunt_id);

// operations

void add_treasure(const char *hunt_id);
void list_treasure(const char *hunt_id);
void view(const char *hunt_id, const char *id);
void remove_treasure(const char *hunt_id, const char *id);
void remove_hunt(const char *hunt_id);

#endif 