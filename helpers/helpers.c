#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief Read input as one big buffer
/// @param filename 
/// @return 
char *
read_input(const char *filename)
{
    FILE *h_input = fopen(filename, "r");
    fseek(h_input, 0L, SEEK_END);
    long fs = ftell(h_input);
    fseek(h_input, 0L, SEEK_SET);

    char *f_buff = malloc(sizeof(char) * fs + 1);
    memset(f_buff, 0, fs + 1);

    size_t rb = fread(f_buff, sizeof(char), fs, h_input);
    if (rb != fs)
    {
        // free(f_buff);
        fprintf(stderr, "WARN: read %zu bytes of %ld of input.txt\n", rb, fs);

        // exit(-1);
    }

    return f_buff;
}

/// @brief Read input as a list of lines 
/// @param filename 
/// @return 
char **
read_input_lines(const char *filename)
{
    char *input = read_input(filename);
    char **lines = calloc(strlen(input), sizeof(char));

    int li = 0;
    char *il = strtok(input, "\n");
    while(il)
    {
        char *new_line = strdup(il);
        
        lines[li] = new_line;
        lines[li][strlen(new_line)] = 0;

        li++;
        il = strtok(NULL, "\n");
    }
    free(input);

    return lines;

}



/// @brief Use with qsort
/// @param elem1 
/// @param elem2 
/// @return 
int comp_int(const void *elem1, const void *elem2)
{
    int f = *((int *)elem1);
    int s = *((int *)elem2);
    if (f > s)
        return 1;
    if (f < s)
        return -1;
    return 0;
}


struct node2
{
    int file_id;
    int offset;
    int size;
} ;

/// @brief Use with qsort
/// @param elem1 
/// @param elem2 
/// @return 
int comp_node2(const void *elem1, const void *elem2)
{
    struct node2 f = *((struct node2 *)elem1);
    struct node2 s = *((struct node2 *)elem2);
    if (f.offset > s.offset)
        return 1;
    if (f.offset < s.offset)
        return -1;
    return 0;
}

