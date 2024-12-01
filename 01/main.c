#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../helpers/helpers.h"

char * read_input();
void part_1(char *input);
void part_2(char *input);

int 
main() {
    printf("merry christmas!\n");

    char *input1 = read_input();
    char *input2 = malloc(sizeof(char) * strlen(input1));
    input2 = strdup(input1);

    part_1(input1);
    part_2(input2);

    return 0;
}

char *
read_input() {
    FILE *h_input = fopen("input.txt", "r");
    fseek(h_input, 0L, SEEK_END);
    long fs = ftell(h_input);
    fseek(h_input, 0L, SEEK_SET);

    char *f_buff = malloc(sizeof(char) * fs + 1);
    memset(f_buff, 0, fs+1);

    size_t rb = fread(f_buff, sizeof(char), fs, h_input);
    if(rb != fs) {
        //free(f_buff);
        fprintf(stderr, "WARN: read %zu bytes of %ld of input.txt\n", rb, fs);
        
        //exit(-1);
    }

    return f_buff;
}

void
part_1(char *input) {
    printf("Part 1:\n");

    char *token = strtok(input, "\n");

    long acc = 0;
    while(token) {
        // printf("%s\n-\n", token);
        // fflush(stdout);

        token = strtok(NULL, "\n");

    }
    free(token);

    int result = 0;
    printf("Result is: %d\n", result);
}

void
part_2(char *input) {
    printf("Part 2:\n");

    char *token = strtok(input, "\n");

    long acc = 0;
    while(token) {
        // printf("%s\n-\n", token);
        // fflush(stdout);

        token = strtok(NULL, "\n");

    }
    free(token);

    int result = 0;
    printf("Result is: %d\n", result);
}