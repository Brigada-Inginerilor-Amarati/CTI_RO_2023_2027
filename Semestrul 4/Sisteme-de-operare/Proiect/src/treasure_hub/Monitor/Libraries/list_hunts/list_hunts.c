#include "list_hunts.h"

int output_fd_pipe = 1;

void list_hunts() {
    DIR *dir = opendir(HUNTS_DIR_PATH);

    if (!dir) {
        write(2, "Error opening directory", 24);
        return;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        // Check if the entry is a directory and not "." or ".."
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char path[BUFFER_SIZE];
            snprintf(path, sizeof(path), "treasure_hunts/%s/treasure.bin", entry->d_name);

            struct stat st;
            if (stat(path, &st) == 0) {
                int count = st.st_size / sizeof(struct Treasure);
                dprintf(output_fd_pipe, "Hunt: %s | Treasures: %d\n", entry->d_name, count);
            }
        }
    }

    closedir(dir);
}