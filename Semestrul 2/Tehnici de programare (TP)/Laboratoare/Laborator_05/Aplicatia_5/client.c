#include "stack.h"
#include <stdio.h>
#include <string.h>

#define STRING_SIZE 100

int main() {
    FILE *input_file = fopen("data.txt", "r");
    if (input_file == NULL) {
        perror("Error opening file");
        return 1;
    }
    char str[STRING_SIZE];
    if (fgets(str, STRING_SIZE, input_file) == NULL) {
        perror("Error reading from file");
        fclose(input_file);
        return 1;
    }
    fclose(input_file);

    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';

    int code = check_validity(str);

    switch (code) {
        case -1:
            printf("Memory allocation failure\n");
            break;
        case 0:
            printf("The string is not valid\n");
            break;
        case 1:
            printf("The string is valid\n");
            break;
    }

    return 0;
}
