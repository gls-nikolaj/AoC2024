#include <stdio.h>
#include <windows.h>

char * read_input();

int 
main() {

    printf("hello, world!\n");

    char *input = read_input();
    long acc = 0;
    for (size_t i = 0; input[i] != 0; i++, acc++) {
        printf("%c", input[i]);
    }

    free(input);    

    return 0;
}

char *
read_input() {
    FILE *h_input = fopen("input.txt", "r");
    fseek(h_input, 0L, SEEK_END);
    long fs = ftell(h_input);
    fseek(h_input, 0L, SEEK_SET);

    char *f_buff = malloc(sizeof(char) * fs + 1);
    size_t rb = fread(f_buff, sizeof(char), fs, h_input);
    f_buff[fs+1] = 0;

    if(rb != fs) {
        fprintf(stderr, "read %zu bytes of %ld of input.txt", rb, fs);
        exit(-1);
    }

    return f_buff;
}