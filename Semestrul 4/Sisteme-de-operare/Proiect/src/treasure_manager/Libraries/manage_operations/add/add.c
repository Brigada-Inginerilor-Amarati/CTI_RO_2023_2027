#include "add.h"


void add_treasure(const char *hunt_id){
    static char dir_path[MAX_PATH_LEN_DIR];
    snprintf(dir_path, sizeof(dir_path), "%s/%s", TREASURE_DIR, hunt_id);

    static char file_path[MAX_PATH_LEN_FILE];
    snprintf(file_path, sizeof(file_path), "%s/%s",dir_path, TREASURE_FILE);

    static char log_path[MAX_PATH_LEN_FILE];
    snprintf(log_path, sizeof(log_path), "%s/%s", dir_path, TREASURE_LOG);

    if(!DIR_exists(TREASURE_DIR)) {
        if (DIR_create(TREASURE_DIR) == -1) {
            printf("Failed to create base directory");
            return;
        }
    }

    if (!DIR_exists(dir_path)) {
        if (DIR_create(dir_path) == -1) {
            printf("Failed to create base directory");
            return;
        }
    }

    // create the file for the new treasure
    int file = FILE_create(file_path);

    if(file == -1){
        return;
    }

    // create the log file for the HUNT
    int log_file = FILE_create(log_path);

    if(log_file == -1){
        close(file);
        return;
    }

    // create the symlink for the HUNT

    if(symlink_create(hunt_id) == -1){
        close(file);
        close(log_file);
        return;
    }

    // read the data for the new treasure
    Treasure_T *treasure_to_be_added = create_treasure();

    if(treasure_to_be_added == NULL){
        close(file);
        close(log_file);
        return;
    }

    // write the data to the file
    ssize_t bytes_written = write(file, treasure_to_be_added, sizeof(Treasure_T));

    if(bytes_written == -1 || bytes_written != sizeof(Treasure_T)){
        printf("Error writing to file");
        close(file);
        close(log_file);
        return;
    }

    // close the file
    if(close(file) == -1){
        printf("Error closing file");
        close(log_file);
        return;
    }

    // write the log entry
    char log_entry[MAX_PATH_LEN_FILE];
    snprintf(log_entry, sizeof(log_entry), "Added treasure with ID %s to hunt %s\n", treasure_to_be_added->id, hunt_id);

    ssize_t bytes_written_log = write(log_file, log_entry, strlen(log_entry));

    if(bytes_written_log == -1 || bytes_written_log != strlen(log_entry)){
        printf("Error writing to log file");
        close(log_file);
        return;
    }

    // close the log file
    if(close(log_file) == -1){
        printf("Error closing log file");
        return;
    }

    // free the memory allocated for the treasure
    free(treasure_to_be_added);
    //printf("Log entry added successfully!\n");
}