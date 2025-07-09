#include "treasure_manager.h"
#include "Libraries/manage_argv/manage_argv.h"
#include "Libraries/manage_operations/manage_operations.h"

Operation_ERROR_T execute_operation(int argc, char **argv){
    Operation_T operation =  read_argv(argc, argv);

    switch(operation){
        case ADD_TREASURE:
            if(argc != 3){
                return OPERATION_FAILED;
            }
            add_treasure(argv[2]);
            break;
        case LIST_TREASURE:
            if(argc != 3){
                return OPERATION_FAILED;
            }
            list_treasure(argv[2]);
            break;
        case VIEW_TREASURE:
            if(argc != 4){
                return OPERATION_FAILED;
            }
            view(argv[2], argv[3]);
            break;
        case REMOVE_TREASURE:
            if(argc != 4){
                return OPERATION_FAILED;
            }
            remove_treasure(argv[2], argv[3]);
            break;
        case REMOVE_HUNT:
            if(argc != 3){
                return OPERATION_FAILED;
            }
            remove_hunt(argv[2]);
            break;
        case HELP:
        default:
            print_help();
            break;
    }
    return NO_ERROR;
}

int main(int argc, char **argv){
    execute_operation(argc, argv);
    return 0;
}