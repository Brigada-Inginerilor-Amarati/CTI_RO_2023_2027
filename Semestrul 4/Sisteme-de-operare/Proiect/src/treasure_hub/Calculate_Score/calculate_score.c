#include "calculate_score.h"

int DIR_exists(const char *dir_path){
    DIR *dir = opendir(dir_path);

    if(!dir){
        return 0;   // directory does not exist
    }
    // printf("Directory exists: %s\n", dir_path);

    closedir(dir);

    return 1;   // directory exists
}

List_Score_T create_list() {
    return NULL; 
}

List_Score_T get_or_create_node(List_Score_T list, const char *userName) {
    List_Score_T current = list;

    // search for the user in the list
    while (current != NULL) {
        if (strcmp(current->userName, userName) == 0) {
            return current;
        }
        current = current->next_node;
    }

    // create a new node if not found

    List_Score_T new_node = (List_Score_T)malloc(sizeof(Nod_Score_T));
    if (!new_node) {
        perror("malloc");
        return NULL;
    }

    // Initialize the new node
    strncpy(new_node->userName, userName, MAX_ID_LEN - 1);
    new_node->userName[MAX_ID_LEN - 1] = '\0';
    new_node->totalScore = 0;
    new_node->next_node = NULL;

    // Insert the new node at the beginning of the list
    new_node->next_node = list;
    return new_node;
}


// This function calculates the score for a specific user in a specific hunt
int calculate_score(const char *hunt_id, const char *userName) {
    char dir_path[MAX_PATH_LEN_DIR];
    snprintf(dir_path, sizeof(dir_path), "%s/%s", TREASURE_DIR, hunt_id);

    char file_path[MAX_PATH_LEN_FILE];
    snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, TREASURE_FILE);

    if (!DIR_exists(dir_path)) {
        fprintf(stderr, "Hunt directory does not exist: %s\n", dir_path);
        return -1;
    }

    int fd = open(file_path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    Treasure_T treasure;
    ssize_t bytes_read;
    int totalScore = 0;

    while ((bytes_read = read(fd, &treasure, sizeof(treasure))) > 0) {
        if (bytes_read != sizeof(treasure)) {
            fprintf(stderr, "Incomplete treasure entry\n");
            close(fd);
            return -1;
        }

        if (strcmp(treasure.userName, userName) == 0) {
            totalScore += treasure.value;
        }
    }

    close(fd);
    return totalScore;
}

// This function calculates the scores for all users in a specific hunt
List_Score_T calculate_all_scores(const char *hunt_id) {
    char dir_path[MAX_PATH_LEN_DIR];
    snprintf(dir_path, sizeof(dir_path), "%s/%s", TREASURE_DIR, hunt_id);

    char file_path[MAX_PATH_LEN_FILE];
    snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, TREASURE_FILE);

    if (!DIR_exists(dir_path)) {
        fprintf(stderr, "Hunt directory does not exist: %s\n", dir_path);
        return NULL;
    }

    int fd = open(file_path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return NULL;
    }

    Treasure_T treasure;
    ssize_t bytes_read;

    List_Score_T list = create_list();

    while ((bytes_read = read(fd, &treasure, sizeof(treasure))) > 0) {
        if (bytes_read != sizeof(treasure)) {
            fprintf(stderr, "Incomplete treasure entry\n");
            close(fd);
            return list;
        }

        List_Score_T node = get_or_create_node(list, treasure.userName);
        if (node == NULL) {
            close(fd);
            return list;
        }

        // Update the score for the user
        node->totalScore += treasure.value;


        // Move the node to the front of the list
        if (node != list && node->next_node == list) {
            list = node;
        }

    }

    close(fd);
    return list;
    
}

void print_scores(List_Score_T list) {
    List_Score_T current = list;
    while (current != NULL) {
        printf("%s: %d\n", current->userName, current->totalScore);
        current = current->next_node;
    }
}

void free_score_list(List_Score_T list) {
    while (list != NULL) {
        List_Score_T tmp = list;
        list = list->next_node;
        free(tmp);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        write(2, "Usage: calculate_score <hunt_id> <userName>\n", 42);
        return 1;
    }

    const char *hunt_id = argv[1];

    List_Score_T scores = calculate_all_scores(hunt_id);

    if (scores == NULL) {
        printf("Failed to calculate scores\n");
        return 1;
    }

    // Print the name of the Hunt directory
    printf("\n--------------\nHunt directory: %s\n---------------\n", hunt_id);
    // Print the scores
    print_scores(scores);
    free_score_list(scores);

    return 0;
}