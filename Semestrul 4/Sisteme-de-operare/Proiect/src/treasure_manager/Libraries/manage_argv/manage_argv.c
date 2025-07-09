#include "manage_argv.h"    

Operation_T read_argv(int argc, char **argv) {
    if (argc < 2) {
        return INVALID_OPERATION;
    }

    // Check the first argument for the operation

    // --add

    if (argc == 3 && strcmp(argv[1], "--add") == 0) {
        return ADD_TREASURE;
    }

    // --list
    else if (argc == 3 && strcmp(argv[1], "--list") == 0) {
        return LIST_TREASURE;
    }

    // --view
    else if (argc == 4 && strcmp(argv[1], "--view") == 0) {
        return VIEW_TREASURE;
    }

    // --remove_treasure
    else if (argc == 4 && strcmp(argv[1], "--remove_treasure") == 0) {
        return REMOVE_TREASURE;
    }

    // --remove_hunt
    else if (argc == 3 && strcmp(argv[1], "--remove_hunt") == 0) {
        return REMOVE_HUNT;
    }

    // --help
    else if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        return HELP;
    }

    // Invalid operation
    print_help();
    return INVALID_OPERATION;
}

void print_help(){
    printf("Usage: ./treasure_manager [operation] [options]\n");
    printf("Operations:\n");
    printf("  --add <hunt_id>             Add a new treasure to a hunt\n");
    printf("  --list <hunt_id>            List all treasures in a hunt\n");
    printf("  --view <hunt_id> <treasure_id> View a specific treasure\n");
    printf("  --remove_treasure <hunt_id> <treasure_id> Remove a treasure\n");
    printf("  --remove_hunt <hunt_id>     Remove an entire hunt\n");
    printf("  --help                      Show this help message\n");
}

