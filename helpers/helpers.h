#ifndef HELPERS_H
#define HELPERS_H

#define bool short
#define true 1
#define false 0

char *read_input(const char *filename);
char **read_input_lines(const char *filename);
int comp_int (const void * elem1, const void * elem2);
int comp_node2 (const void * elem1, const void * elem2);

#endif 