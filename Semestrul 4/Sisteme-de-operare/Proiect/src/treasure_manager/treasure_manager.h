#ifndef __TREASURE_MANAGER_H__
#define __TREASURE_MANAGER_H__

// ---------------------------------------
// Header files
// ---------------------------------------

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>


// ---------------------------------------
// Defines
// ---------------------------------------

#define TREASURE_DIR "treasure_hunts"
#define TREASURE_FILE "treasure.bin"
#define TREASURE_LOG "logged_hunt.txt"
#define TREASURE_SYMLINK "logged_hunt"    


#define MAX_ID_LEN 16
#define MAX_USERNAME_LEN 32
#define MAX_CLUETEXT_LEN 128
#define MAX_PATH_LEN_DIR 256
#define MAX_PATH_LEN_FILE 512

#define PERMISSIONS (S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) // 0777
#define CREATE_FILE (O_WRONLY | O_CREAT | O_APPEND)     

// ---------------------------------------
// Data Structures
// ---------------------------------------

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

typedef enum {
    INVALID_OPERATION,
    HELP,
    ADD_TREASURE,
    LIST_TREASURE,
    VIEW_TREASURE,
    REMOVE_TREASURE,
    REMOVE_HUNT
} Operation_T;

typedef enum{
    NO_ERROR,
    OPERATION_FAILED,
    OPERATION_ERROR
}Operation_ERROR_T;

#endif 

