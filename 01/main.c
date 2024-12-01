#include <stdio.h>
// #include <windows.h>
#include <stdlib.h>
#include <string.h>

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

int 
comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}


void
part_1(char *input) {
    printf("Part 1:\n");


    // input list is 1000 items
    int li = 0;
    int *l_list = malloc(sizeof(int) * 1000);
    int *r_list = malloc(sizeof(int) * 1000);

    char *token = strtok(input, "\n");

    char line[20] ;
    long acc = 0;
    while(token) {
        
        strcpy(line, token);

        char *numtok = strtok(line, "   ");
        int num = atoi(numtok);
        l_list[li] = num;

        numtok = strtok(NULL, " ");
        num = atoi(numtok);
        r_list[li++] = num;

        token += strlen(token) + 1;
        token = strtok(token, "\n");

    }
    free(token);

    qsort(l_list, 1000, sizeof(*l_list), comp);
    qsort(r_list, 1000, sizeof(*r_list), comp);

    int result = 0;
    for(int i = 0 ; i < 1000; i++) {
        int diff = 0;
        if(l_list[i] > r_list[i]) 
            diff = l_list[i] - r_list[i];
        else 
            diff = r_list[i] - l_list[i];

        printf("% 5d\t% 5d => % 3d\n", l_list[i], r_list[i], diff);
        result += diff;
    }

    free(l_list);
    free(r_list);

    printf("Result is: %d\n", result);
}

void
part_2(char *input) {
    printf("Part 2:\n");

    // input list is 1000 items
    int li = 0;
    int *l_list = malloc(sizeof(int) * 1000);
    int *r_list = malloc(sizeof(int) * 1000);

    char *token = strtok(input, "\n");

    char line[20] ;
    long acc = 0;
    while(token) {
        
        strcpy(line, token);

        char *numtok = strtok(line, "   ");
        int num = atoi(numtok);
        l_list[li] = num;

        numtok = strtok(NULL, " ");
        num = atoi(numtok);
        r_list[li++] = num;

        token += strlen(token) + 1;
        token = strtok(token, "\n");

    }
    free(token);

    int result = 0;
    for(int i = 0 ; i < 1000; i++) {
        for(int j = 0; j < 1000; j++) {
            if(r_list[j] == l_list[i]) {
                result += l_list[i];
            }
        }
    }

    free(l_list);
    free(r_list);
    printf("Result is: %d\n", result);
}