#include <unistd.h>
#include "treasure.h"

// helper functions

Treasure_T *create_treasure(){
    Treasure_T *treasure_to_be_added = malloc(sizeof(Treasure_T));

    if(treasure_to_be_added == NULL){
        perror("Error allocating memory");
        return NULL;
    }

    printf("Enter treasure data: \n");

    printf("ID (max %d chars): ", MAX_ID_LEN-1);

    if (scanf("%15s", treasure_to_be_added->id) != 1) {
        free(treasure_to_be_added);
        return NULL;
    }


    printf("Username (max %d chars): ", MAX_USERNAME_LEN-1);

    if (scanf("%31s", treasure_to_be_added->userName) != 1) {
        free(treasure_to_be_added);
        return NULL;
    }

    printf("Latitude: ");
    scanf("%f", &treasure_to_be_added->GPSCoordinate.latitude);

    printf("Longitude: ");
    scanf("%f", &treasure_to_be_added->GPSCoordinate.longitude);
    printf("Clue text: ");

    getchar(); 
    fgets(treasure_to_be_added->clueText, MAX_CLUETEXT_LEN, stdin);
    treasure_to_be_added->clueText[strcspn(treasure_to_be_added->clueText, "\n")] = 0;

    printf("Value: ");
    scanf("%d", &treasure_to_be_added->value);


    return treasure_to_be_added;
}

int DIR_exists(const char *dir_path){
    DIR *dir = opendir(dir_path);

    if(!dir){
        return 0;   // directory does not exist
    }

    closedir(dir);

    return 1;   // directory exists
}

int DIR_create(const char *dir_path) {
    if (DIR_exists(dir_path)) {
        return 0;
    }

    if (mkdir(dir_path, 0755) == -1){
        return -1;
    } 
    
    return 1;
}

int FILE_create(const char *file_path){
    int file = open(file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);

    if(file == -1){
        printf("Error opening/appending file");
        return -1;
    }

    return file;
}

int symlink_create(const char *hunt_id){
    // target -> root directory
    char target_path[MAX_PATH_LEN_DIR];
    snprintf(target_path, sizeof(target_path), "%s/%s/%s", TREASURE_DIR, hunt_id, TREASURE_LOG);

    char link_name[MAX_PATH_LEN_DIR];
    snprintf(link_name, sizeof(link_name), "%s-%s", TREASURE_SYMLINK, hunt_id);

    struct stat sb;

    if (lstat(link_name, &sb) == 0) {
        if (S_ISLNK(sb.st_mode)) {
            printf("Symlink already exists: %s\n", link_name);
            return 0;
        } else {
            printf("%s is not a symlink!\n", link_name);
            return -1;
        }
    }

    if(symlink(target_path, link_name) == -1){
        printf("Error creating symlink\n");
        return -1;
    }

    printf("Symlink created successfully: %s -> %s\n", link_name, target_path);

    return 1;

}

// operations

void add_treasure(const char *hunt_id){

    static char dir_path[MAX_PATH_LEN_DIR];
    snprintf(dir_path, sizeof(dir_path), "%s/%s", TREASURE_DIR, hunt_id);

    static char file_path[MAX_PATH_LEN_FILE];
    snprintf(file_path, sizeof(file_path), "%s/%s",dir_path, TREASURE_FILE);

    static char log_path[MAX_PATH_LEN_FILE];
    snprintf(log_path, sizeof(log_path), "%s/%s", dir_path, TREASURE_LOG);


    if (!DIR_exists(TREASURE_DIR)) {
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
    Treasure_T* treasure_to_be_added = create_treasure();

    if(treasure_to_be_added == NULL){
        return;
    }   
    
    // write the treasure data to the file
    ssize_t bytes_written = write(file, treasure_to_be_added, sizeof(Treasure_T));

    if(bytes_written == -1 || bytes_written != sizeof(Treasure_T)){
        printf("Error writing to file");
        close(file);
        return;
    }

    close(file);


    char log_entry[MAX_PATH_LEN_FILE];
    snprintf(log_entry, sizeof(log_entry), "Added treasure with ID: %s - user: %s\n", treasure_to_be_added->id, treasure_to_be_added->userName);

    ssize_t bytes_written_log = write(log_file, log_entry, strlen(log_entry));

    if(bytes_written_log == -1 || bytes_written_log != strlen(log_entry)){
        printf("Error writing to log file");
        close(log_file);
        return;
    }

    close(log_file);

    //printf("Log entry added successfully!\n");
}

void list_treasure(const char *hunt_id){
    static char dir_path[MAX_PATH_LEN_DIR];
    snprintf(dir_path, sizeof(dir_path), "%s/%s", TREASURE_DIR, hunt_id);

    static char file_path[MAX_PATH_LEN_FILE];
    snprintf(file_path, sizeof(file_path), "%s/%s",dir_path, TREASURE_FILE);

    static char log_path[MAX_PATH_LEN_FILE];
    snprintf(log_path, sizeof(log_path), "%s/%s", dir_path, TREASURE_LOG);

    if (!DIR_exists(dir_path)) {
        printf("Hunt directory does not exist\n");
        return;
    }

    printf("Hunt name: %s\n\n", hunt_id);

    struct stat file_stat;
    if(stat(file_path, &file_stat) == -1){
        printf("Error getting file info");
        return;
    }

    printf("File size: %ld bytes\n\n", file_stat.st_size);

    printf("Last modification time: %ld\n\n", file_stat.st_mtime);

    int file = open(file_path, O_RDONLY);

    if(file == -1){
        printf("Error opening file");
        return;
    }

    int log_file = FILE_create(log_path);

    if(log_file == -1){
        close(file);
        return;
    }

    Treasure_T treasure;
    ssize_t bytes_read;

    while((bytes_read = read(file, &treasure, sizeof(treasure))) > 0){
        // if the number of bytes read is not equal to the size of the struct, there is an error
        if(bytes_read != sizeof(treasure)){
            printf("Error reading file");
            close(file);
            return;
        }

        printf("ID: %s\n", treasure.id);
        printf("Username: %s\n", treasure.userName);
        printf("Latitude: %f\n", treasure.GPSCoordinate.latitude);
        printf("Longitude: %f\n", treasure.GPSCoordinate.longitude);
        printf("Clue text: %s\n", treasure.clueText);
        printf("Value: %d\n", treasure.value);
        printf("\n");
    }

    if(close(file) == -1){
        printf("Error closing file");
        return;
    }

    char log_entry[MAX_PATH_LEN_FILE];

    snprintf(log_entry, sizeof(log_entry), "Listed all treasures in hunt %s\n", hunt_id);

    ssize_t bytes_written_log = write(log_file, log_entry, strlen(log_entry));

    if(bytes_written_log == -1 || bytes_written_log != strlen(log_entry)){
        printf("Error writing to log file");
        close(log_file);
        return;
    }

    if(close(log_file) == -1){
        printf("Error closing log file");
        return;
    }

    //printf("Log entry added successfully!\n");
}

void view(const char *hunt_id, const char *id){
    static char dir_path[MAX_PATH_LEN_DIR];
    snprintf(dir_path, sizeof(dir_path), "%s/%s", TREASURE_DIR, hunt_id);

    static char file_path[MAX_PATH_LEN_FILE];
    snprintf(file_path, sizeof(file_path), "%s/%s",dir_path, TREASURE_FILE);

    static char log_path[MAX_PATH_LEN_FILE];
    snprintf(log_path, sizeof(log_path), "%s/%s", dir_path, TREASURE_LOG);

    if (!DIR_exists(dir_path)) {
        printf("Hunt directory does not exist\n");
        return;
    }

    int file = open(file_path, O_RDONLY);

    if(file == -1){
        printf("Error opening file");
        return;
    }

    int log_file = FILE_create(log_path);

    if(log_file == -1){
        close(file);
        return;
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
            return;
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
    }

    if(close(file) == -1){
        perror("Error closing file");
        return;
    }


    char log_entry[MAX_PATH_LEN_FILE];

    snprintf(log_entry, sizeof(log_entry), "Viewed treasure with ID %s, user %s in hunt %s\n", id, username_forLOG, hunt_id);

    ssize_t bytes_written_log = write(log_file, log_entry, strlen(log_entry));

    if(bytes_written_log == -1 || bytes_written_log != strlen(log_entry)){
        printf("Error writing to log file");
        close(log_file);
        return;
    }

    if(close(log_file) == -1){
        printf("Error closing log file");
        return;
    }

    //printf("Log entry added successfully!\n");
}

void remove_treasure(const char *hunt_id, const char *id) {
    static char dir_path[MAX_PATH_LEN_DIR];
    snprintf(dir_path, sizeof(dir_path), "%s/%s", TREASURE_DIR, hunt_id);

    static char file_path[MAX_PATH_LEN_FILE];
    snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, TREASURE_FILE);

    char temp_file_path[MAX_PATH_LEN_FILE];
    snprintf(temp_file_path, sizeof(temp_file_path), "%s/copy_%s", dir_path, TREASURE_FILE);

    static char log_file_path[MAX_PATH_LEN_FILE];
    snprintf(log_file_path, sizeof(log_file_path), "%s/%s", dir_path, TREASURE_LOG);


    if (!DIR_exists(dir_path)) {
        printf("Hunt directory does not exist\n");
        return;
    }

    int file = open(file_path, O_RDONLY);
    if (file == -1) {
        perror("Error opening file");
        return;
    }

    int temp_file = open(temp_file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (temp_file == -1) {
        perror("Error creating temporary file");
        close(file);
        return;
    }

    Treasure_T treasure;
    ssize_t bytes_read;
    int found = 0;

    while ((bytes_read = read(file, &treasure, sizeof(treasure))) > 0) {
        if (bytes_read != sizeof(treasure)) {
            perror("Error reading file");
            close(file);
            close(temp_file);
            return;
        }

        if (strcmp(treasure.id, id) != 0) {
            if (write(temp_file, &treasure, sizeof(treasure)) != sizeof(treasure)) {
                perror("Error writing to temporary file");
                close(file);
                close(temp_file);
                return;
            }
        } else {
            found = 1;
        }
    }

    if (!found) {
        printf("Error: No treasure found with ID '%s'\n", id);
        close(file);
        close(temp_file);
        unlink(temp_file_path); // Remove temp file
        return;
    }

    close(file);
    close(temp_file);

    // Replace original file with temp file
    if (rename(temp_file_path, file_path) == -1) {
        perror("Error renaming temporary file");
        return;
    }

    // Check if the new file is empty
    struct stat new_file_stat;
    if (stat(file_path, &new_file_stat) == -1) {
        perror("Error getting file info");
        return;
    }

    int log_file = FILE_create(log_file_path);

    if(log_file == -1){
        return;
    }

    char log_entry[MAX_PATH_LEN_FILE];


    if (new_file_stat.st_size == 0) {
        if (unlink(file_path) == -1) {
            perror("Error removing empty file");
            return;
        }

        // // Remove the symlink if it exists
        // char symlink_path[MAX_PATH_LEN_FILE];
        // snprintf(symlink_path, sizeof(symlink_path), "%s-%s", TREASURE_SYMLINK, hunt_id);

        // struct stat sb;

        // if (lstat(symlink_path, &sb) == 0) {
        //     if (S_ISLNK(sb.st_mode)) {
        //         // E un symlink
        //         unlink(symlink_path);
        //     } else {
        //         printf("%s is not a symlink!\n", symlink_path);
        //     }
        // } else {
        //     printf("Symlink %s does not exist\n", symlink_path);
        // }

        
        //printf("All treasures removed. Deleted empty hunt file.\n");

        snprintf(log_entry, sizeof(log_entry), "Treasure with ID %s was removed. There were no more treasures in hunt %s so the empty file(treasure.bin) was deleted\n", id, hunt_id);
    } else {
        //printf("Treasure with ID '%s' removed successfully!\n", id);
        snprintf(log_entry, sizeof(log_entry), "Treasure with ID %s was removed in hunt %s\n", id, hunt_id);
    }

    ssize_t bytes_written_log = write(log_file, log_entry, strlen(log_entry));

    if (bytes_written_log == -1 || bytes_written_log != strlen(log_entry)) {
        printf("Error writing to log file");
        close(log_file);
        return;
    }

    if (close(log_file) == -1) {
        printf("Error closing log file");
        return;
    }
}
 
// no details to add in log here 
void remove_hunt(const char *hunt_id){
    static char dir_path[MAX_PATH_LEN_DIR];
    snprintf(dir_path, sizeof(dir_path), "%s/%s", TREASURE_DIR, hunt_id);

    if(!DIR_exists(dir_path)) {
        printf("Hunt directory does not exist\n");
        return;
    }

    // remove the files within the directory

    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        printf("Error opening directory\n");
        return;
    }

    struct dirent *entry;
    char file_path[MAX_PATH_LEN_FILE];

    while ((entry = readdir(dir)) != NULL) {
        // skip the current and parent directory entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entry->d_name);
        if (unlink(file_path) == -1) {      
            printf("Error removing file: %s\n", file_path);
            closedir(dir);
            return;
        }
    }

    char symlink_path[MAX_PATH_LEN_FILE];
    snprintf(symlink_path, sizeof(symlink_path), "%s-%s", TREASURE_SYMLINK, hunt_id);

    struct stat sb;
    if (lstat(symlink_path, &sb) == 0) {
        if (S_ISLNK(sb.st_mode)) {
            unlink(symlink_path);
        } else {
            printf("%s is not a symlink!\n", symlink_path);
        }
    }
    else {
        printf("Symlink %s does not exist\n", symlink_path);
    }

    closedir(dir);

    // remove the now empty directory
    if (rmdir(dir_path) == -1) {
        printf("Error removing directory\n");
        return;
    }
    printf("Hunt removed successfully!\n");
}