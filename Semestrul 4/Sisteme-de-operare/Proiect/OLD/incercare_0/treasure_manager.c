#include "treasure.h"

void print_help(void) {
    printf("Treasure Manager - Usage:\n");
    printf("  --add <hunt_id>             Add a new treasure to a hunt\n");
    printf("  --list <hunt_id>            List all treasures in a hunt\n");
    printf("  --view <hunt_id> <treasure_id> View a specific treasure\n");
    printf("  --remove_treasure <hunt_id> <treasure_id> Remove a treasure\n");
    printf("  --remove_hunt <hunt_id>     Remove an entire hunt\n");
    printf("  --help                      Show this help message\n");
}

int main(int argc, char **argv){
    if(argc < 2){
        print_help();
        return 1;
    }

    if(strcmp(argv[1], "--add") == 0){
        if(argc < 3){
            printf("Error: Hunt ID is required\n");
            print_help();
            return 1;
        }
        add_treasure(argv[2]);
    }
    else if(strcmp(argv[1], "--list") == 0){
        if(argc < 3){
            printf("Error: Hunt ID is required\n");
            print_help();
            return 1;
        }
        list_treasure(argv[2]);
    }
    else if(strcmp(argv[1], "--view") == 0){
        if(argc < 4){
            printf("Error: Treasure ID is required\n");
            print_help();
            return 1;
        }
        view(argv[2], argv[3]);
    }
    else if(strcmp(argv[1], "--remove_treasure") == 0){
        if(argc < 4){
            printf("Error: Treasure ID is required\n");
            print_help();
            return 1;
        }
        remove_treasure(argv[2], argv[3]);
    }
    else if(strcmp(argv[1], "--remove_hunt") == 0){
        if(argc < 3){
            printf("Error: Hunt ID is required\n");
            print_help();
            return 1;
        }
        remove_hunt(argv[2]);
    }
    else if(strcmp(argv[1], "--help") == 0){
        print_help();
    }
    else{
        print_help();
        return 1;
    }

    return 0;
}