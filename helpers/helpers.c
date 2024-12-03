#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *
read_input(const char *filename) {
    FILE *h_input = fopen(filename, "r");
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

int 
comp_int (const void * elem1, const void * elem2) {
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}