#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void concatenate(FILE* inputfile, FILE* outputfile);

// argmum is the number of argument, arr_str is the array of arguments
int main(int argnum, char *arr_str[]) {
    FILE *outputfile = stdout;
    char *output_filename = NULL;
    int opt;

    // typical getopt loop to parse command line options
    while ((opt = getopt(argnum, arr_str, "o:")) != -1) {
        switch (opt) {
            case 'o':
                output_filename = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s [-o outfile] infile1 [...infile2...]\n", arr_str[0]);
                exit(EXIT_FAILURE);
        }
    }
    // write to the output file if it is not stdout
    if (output_filename) {
        outputfile = fopen(output_filename, "w");
        if (!outputfile) {
            perror("Error opening output file");
            exit(EXIT_FAILURE);
        }
    }

    // if there is no argument, print error message
    if (optind >= argnum) {
        fprintf(stderr, "error! No arguments example: ./maxcat1 file1 file2 or ./maxcat1 -o output file1\n");
        exit(EXIT_FAILURE);
    } else {
        for (int i = optind; i < argnum; i++) {
            // for some reason I kept having to use CTRL+D to indicate end of input (didn't have enough time to fix it)
            // thus I put a message to indicate that
            if (strcmp(arr_str[i], "-") == 0) {
                fprintf(stderr, "Waiting for input from standard input. Use CTRL+D to indicate end of input.\n");

                concatenate(stdin, outputfile);
            } else {
                FILE *inputfile = fopen(arr_str[i], "r");
                if (!inputfile) {
                    perror("There is an error opening the file! \n");
                    exit(EXIT_FAILURE);
                }
                concatenate(inputfile, outputfile);
                fclose(inputfile);
            }
        }
    }

    if (outputfile != stdout) {
        fclose(outputfile);
    }

    return 0;
}

// concatenate the input file to the output file
void concatenate(FILE* inputfile, FILE* outputfile) {
    int character;

    while ((character = fgetc(inputfile)) != EOF) {
        fputc(character, outputfile);
    }

    fprintf(stderr, "File processed successfully.\n");
}
