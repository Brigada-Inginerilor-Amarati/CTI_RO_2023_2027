// ./prog.c fin.txt fout.txt

// test argumente
// deschidere fin.txt
// creare fout.txt
// parcurgere cu read 
// nr caractere alfanumerice


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>

int main(int argc, char **argv){
    if(argc != 3){
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    int fin = open(argv[1], O_RDONLY);

    if(fin < 0){
        printf("Error opening input file: %s\n", argv[1]);
        return 1;
    }

    int fout = open(argv[2], O_WRONLY);

    if(fout < 0){
        printf("Error creating output file: %s\n", argv[2]);
        return 1;
    }

    char buffer[1024];
    ssize_t bytesRead;

    int alphanumericCount = 0;

    while((bytesRead = read(fin, buffer, sizeof(buffer))) > 0){
        for(int i = 0; i < bytesRead; i++){
            if(isalpha(buffer[i])){
                alphanumericCount++;
            }
        }
    }

    printf("Number of alphanumeric characters: %d\n", alphanumericCount);

    if(bytesRead < 0){
        printf("Error reading input file\n");
        close(fin);
        close(fout);
        return 1;
    }

    // Write the count to the output file


    return 0;
}