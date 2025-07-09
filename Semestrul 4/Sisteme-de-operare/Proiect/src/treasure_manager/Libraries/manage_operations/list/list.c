#include "list.h"

void list_treasure(const char *hunt_id){
    static char dir_path[MAX_PATH_LEN_DIR];
    snprintf(dir_path, sizeof(dir_path), "%s/%s", TREASURE_DIR, hunt_id);

    static char file_path[MAX_PATH_LEN_FILE];
    snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, TREASURE_FILE);

    static char log_path[MAX_PATH_LEN_FILE];
    snprintf(log_path, sizeof(log_path), "%s/%s", dir_path, TREASURE_LOG);

    if (!DIR_exists(dir_path)) {
        printf("Hunt directory does not exist\n");
        return ;
    }

    printf("Hunt name: %s\n\n", hunt_id);

    struct stat file_stat;
    if(stat(file_path, &file_stat) == -1){
        printf("Error getting file status\n");
        return ;
    }

    printf("File size: %ld bytes\n", file_stat.st_size);

    time_t last_mod_time = file_stat.st_mtime;

    if(last_mod_time == 0){
        printf("File has not been modified\n");
        return ;
    }
    else{
        char *time_str = ctime(&last_mod_time);
        if(time_str == NULL){
            printf("Error converting time to string\n");
            return ;
        }
        printf("Last modification time: %s\n", time_str);
    }

    //printf("Last modification time: %ld\n", file_stat.st_mtime);

    int file = open(file_path, O_RDONLY);

    if(file == -1){
        printf("Error opening file\n");
        return ;
    }

    int log_file = FILE_create(log_path);

    if(log_file == -1){
        close(file);
        return ;
    }

    Treasure_T treasure;

    ssize_t bytes_read;

    while((bytes_read = read(file, &treasure, sizeof(treasure))) > 0){
        // if the number of bytes read is not equal to the size of the struct, there is an error
        if(bytes_read != sizeof(treasure)){
            printf("Error reading file\n");
            close(file);
            return ;
        }

        printf("ID: %s\n", treasure.id);
        printf("User: %s\n", treasure.userName);
        printf("Latitude: %f\n", treasure.GPSCoordinate.latitude);
        printf("Longitude: %f\n", treasure.GPSCoordinate.longitude);
        printf("Clue: %s\n", treasure.clueText);
        printf("Value: %d\n", treasure.value);
        printf("\n");
    }

    if(close(file) == -1){
        printf("Error closing file\n");
        return ;
    }

    char log_entry[MAX_PATH_LEN_FILE];

    snprintf(log_entry, sizeof(log_entry), "Listed all treasures in hunt %s\n", hunt_id);

    ssize_t bytes_written_log = write(log_file, log_entry, strlen(log_entry));

    if(bytes_written_log == -1 || bytes_written_log != strlen(log_entry)){
        printf("Error writing to log file\n");
        close(log_file);
        return ;
    }

    if(close(log_file) == -1){
        printf("Error closing log file\n");
        return ;
    }

    //printf("Log entry added successfully!\n");
}

void view(const char *hunt_id, const char *id){
    static char dir_path[MAX_PATH_LEN_DIR];
    snprintf(dir_path, sizeof(dir_path), "%s/%s", TREASURE_DIR, hunt_id);

    static char file_path[MAX_PATH_LEN_FILE];
    snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, TREASURE_FILE);

    static char log_path[MAX_PATH_LEN_FILE];
    snprintf(log_path, sizeof(log_path), "%s/%s", dir_path, TREASURE_LOG);

    if (!DIR_exists(dir_path)) {
        printf("Hunt directory does not exist\n");
        return ;
    }

    int file = open(file_path, O_RDONLY);

    if(file == -1){
        printf("Error opening file\n");
        return ;
    }

    int log_file = FILE_create(log_path);

    if(log_file == -1){
        close(file);
        return ;
    }

    Treasure_T treasure;
    ssize_t bytes_read;

    char username_forLOG[MAX_USERNAME_LEN];

    int found = 0;

    printf("Searching for treasure with ID: %s\n", id);
    while ((bytes_read = read(file, &treasure, sizeof(treasure))) > 0) {
        if(bytes_read != sizeof(treasure)){
            printf("Error reading file\n");
            close(file);
            return ;
        }

        if (strcmp(treasure.id, id) == 0) {
            printf("ID: %s\n", treasure.id);
            printf("Username: %s\n", treasure.userName);
            snprintf(username_forLOG, sizeof(username_forLOG), "%s", treasure.userName);
            printf("Coordinates: %f, %f\n", 
                  treasure.GPSCoordinate.latitude,
                  treasure.GPSCoordinate.longitude);
            printf("Clue: %s\n", treasure.clueText);
            printf("Value: %d\n", treasure.value);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Error: No treasure found with ID '%s'\n", id);
        close(file);
        return ;
    }

    if(close(file) == -1){
        perror("Error closing file");
        return ;
    }

    char log_entry[MAX_PATH_LEN_FILE];

    snprintf(log_entry, sizeof(log_entry), "Viewed treasure with ID %s, user %s in hunt %s\n", id, username_forLOG, hunt_id);

    ssize_t bytes_written_log = write(log_file, log_entry, strlen(log_entry));

    if(bytes_written_log == -1 || bytes_written_log != strlen(log_entry)){
        printf("Error writing to log file");
        close(log_file);
        return ;
    }

    if(close(log_file) == -1){
        printf("Error closing log file");
        return ;
    }

    //printf("Log entry added successfully!\n");
}