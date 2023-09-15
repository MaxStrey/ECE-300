#include <stdio.h>
#include <stdlib.h>

// Define buffer size
#define BUFFER_SIZE 4096

// Function concatenate
void concatenate(FILE* inputfile, FILE* outputfile);

// parameters: argnum is the number of arguments, arr_str is an array of strings
int main(int argnum, char *arr_str[]){
    FILE *outputfile = stdout;

    // If no arguments are given, print usage message
    if (argnum < 2){
        fprintf(stderr, "error! No arguments example: ./maxcat file1 [...file2....] \n");
        exit(EXIT_FAILURE);
    }

    for(int i  = 1; i < argnum; i++){
        FILE *inputfile = fopen(arr_str[i], "r");
        if (!inputfile){
            perror("There is an error opening the file! \n");
            exit(EXIT_FAILURE);
        }
        concatenate(inputfile, outputfile);
        fclose(inputfile);
    }
    return 0;

}

// concatenate function
// Takes in two files, inputfile and outputfile, and writes the contents of inputfile to outputfile with fgetc and fputc
void concatenate(FILE* inputfile, FILE* outputfile){
    int character;
    while ((character = fgetc(inputfile)) != EOF){
        fputc(character, outputfile);
    }
}