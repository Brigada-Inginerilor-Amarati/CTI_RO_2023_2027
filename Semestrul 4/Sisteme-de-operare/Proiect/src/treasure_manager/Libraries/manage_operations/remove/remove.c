#include "remove.h"

Operation_ERROR_T remove_treasure(const char *hunt_id, const char *id) {
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
        return OPERATION_ERROR;
    }

    int file = open(file_path, O_RDONLY);
    if (file == -1) {
        perror("Error opening file");
        return OPERATION_ERROR;
    }

    int temp_file = open(temp_file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (temp_file == -1) {
        perror("Error creating temporary file");
        close(file);
        return OPERATION_ERROR;
    }

    Treasure_T treasure;
    ssize_t bytes_read;
    int found = 0;

    while ((bytes_read = read(file, &treasure, sizeof(treasure))) > 0) {
        if (bytes_read != sizeof(treasure)) {
            perror("Error reading file");
            close(file);
            close(temp_file);
            return OPERATION_ERROR;
        }

        if (strcmp(treasure.id, id) != 0) {
            if (write(temp_file, &treasure, sizeof(treasure)) != sizeof(treasure)) {
                perror("Error writing to temporary file");
                close(file);
                close(temp_file);
                return OPERATION_ERROR;
            }
        } else {
            found = 1;
        }
    }

    if (!found) {
        printf("Error: No treasure found with ID '%s'\n", id);
        close(file);
        close(temp_file);
        unlink(temp_file_path);
        return OPERATION_ERROR;
    }

    if (close(file) == -1) {
        perror("Error closing file");
        close(temp_file);
        return OPERATION_ERROR;
    }

    if (close(temp_file) == -1) {
        perror("Error closing temporary file");
        return OPERATION_ERROR;
    }

    if (rename(temp_file_path, file_path) == -1) {
        perror("Error renaming temporary file");
        return OPERATION_ERROR;
    }

    struct stat new_file_stat;

    if (stat(file_path, &new_file_stat) == -1) {
        perror("Error getting file info");
        return OPERATION_ERROR;
    }

    int log_file = FILE_create(log_file_path);

    if (log_file == -1) {
        return OPERATION_ERROR;
    }

    char log_entry[MAX_PATH_LEN_FILE];

    if(new_file_stat.st_size == 0) {
        if (unlink(file_path) == -1) {
            perror("Error removing empty file");
            close(log_file);
            return OPERATION_ERROR;
        }

        char symlink_path[MAX_PATH_LEN_FILE];
        snprintf(symlink_path, sizeof(symlink_path), "%s-%s", TREASURE_SYMLINK, hunt_id);

        if (unlink(symlink_path) == -1) {
            perror("Error removing symlink");
            close(log_file);
            return OPERATION_ERROR;
        }

        snprintf(log_entry, sizeof(log_entry), "Treasure with ID %s was removed. There were no more treasures in hunt %s so the empty file(treasure.bin) was deleted\n", id, hunt_id);
    } else {
        snprintf(log_entry, sizeof(log_entry), "Treasure with ID %s was removed in hunt %s\n", id, hunt_id);
    }

    ssize_t bytes_written_log = write(log_file, log_entry, strlen(log_entry));

    if (bytes_written_log == -1 || bytes_written_log != strlen(log_entry)) {
        printf("Error writing to log file");
        close(log_file);
        return OPERATION_ERROR;
    }

    if (close(log_file) == -1) {
        perror("Error closing log file");
        return OPERATION_ERROR;
    }

    return NO_ERROR;
}

Operation_ERROR_T remove_hunt(const char *hunt_id) {
    static char dir_path[MAX_PATH_LEN_DIR];
    snprintf(dir_path, sizeof(dir_path), "%s/%s", TREASURE_DIR, hunt_id);

    if (!DIR_exists(dir_path)) {
        printf("Hunt directory does not exist\n");
        return OPERATION_ERROR;
    }

    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        printf("Error opening directory");
        return OPERATION_ERROR;
    }

    struct dirent *entry;
    char file_path[MAX_PATH_LEN_FILE];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entry->d_name);
        if (unlink(file_path) == -1) {
            perror("Error removing file");
            closedir(dir);
            return OPERATION_ERROR;
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
    } else {
        printf("Symlink %s does not exist\n", symlink_path);
    }

    closedir(dir);

    if (rmdir(dir_path) == -1) {
        printf("Error removing directory");
        return OPERATION_ERROR;
    }

    return NO_ERROR;
}

