#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../helpers/helpers.h"

void part_1(char *input);
void part_2(char *input);

int 
main() {
    printf("merry christmas!\n");

    char *input1 = read_input("input.txt");
    char *input2 = malloc(sizeof(char) * strlen(input1));
    input2 = strdup(input1);

    part_1(input1);
    part_2(input2);

    return 0;
}


void
part_1(char *input) {
    printf("Part 1:\n");

    char *line = strtok(input, "\n");

    while (line) // iterate lines
    {
        int ni = 0;
        int numbers[10]; // example: used to store numbers

        int line_length = strlen(line); // store for later
        char *numTok = strtok(line, " "); // start tokenizing on " "

        while (numTok) // iterate words in line
        {
            numbers[ni++] = atoi(numTok); // example: parse and store number

            numTok = strtok(NULL, " "); // keep iterating inner loop
        }


        // Skip for strtok to continue working on lines again
        line += line_length + 1;
        line = strtok(line, "\n");
    }
    free(line);

    int result = 0;
    printf("Result is: %d\n", result);
}

void
part_2(char *input) {
    printf("Part 2:\n");

    int result = 0;
    printf("Result is: %d\n", result);
}