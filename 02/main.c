#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../helpers/helpers.h"

void part_1(char *input);
void part_2(char *input);

int main()
{
    printf("merry christmas!\n");

    char *input1 = read_input();
    char *input2 = malloc(sizeof(char) * strlen(input1));
    input2 = strdup(input1);

    part_1(input1);
    part_2(input2);

    return 0;
}

/// @brief
///    The levels are either all increasing or all decreasing.
///    Any two adjacent levels differ by at least one and at most three.
/// @param numbers
/// @param len
/// @return
int is_good(int *numbers, int len)
{
    int incr = numbers[1] > numbers[0];
    for (int i = 1; i < len; i++)
    {
        int cur = numbers[i];
        int prev = numbers[i - 1];
        if (incr && prev > cur)
        {
            return 0;
        }
        else if (!(incr) && cur > prev)
        {
            return 0;
        }

        int diff = abs(cur - prev);
        if (diff < 1 || diff > 3)
        {
            return 0;
        }
    }

    return 1;
}

void part_1(char *input)
{
    printf("Part 1:\n");

    char *line = strtok(input, "\n");

    int goods = 0;
    int bads = 0;
    while (line)
    {
        int ni = 0;
        int numbers[10];
        int line_length = strlen(line);
        char *numTok = strtok(line, " ");

        while (numTok)
        {
            numbers[ni++] = atoi(numTok);
            numTok = strtok(NULL, " ");
        }

        if (is_good(numbers, ni))
        {
            goods++;
        }
        else
        {
            bads++;
        }

        line += line_length + 1;
        line = strtok(line, "\n");
    }
    free(line);

    int result = goods;
    printf("Result is: %d\n", result);
}

int is_good_with_skip(int *numbers, int len)
{

    // if good it's good :)
    if (is_good(numbers, len))
        return 1;

    int tmp[10];
    int success = 1;
    for (int skipper = 0; skipper < len; skipper++)
    {
        for(int i = 0, j = 0; i < len; i++) 
        {
            if(skipper == i) continue;

            tmp[j++] = numbers[i];
        }

        if(is_good(tmp, len-1)) 
        {
            return 1;
        }
    }

    return 0;
}

void part_2(char *input)
{
    printf("Part 2:\n");

    char *line = strtok(input, "\n");

    int goods = 0;
    while (line)
    {
        int ni = 0;
        int numbers[10];
        int line_length = strlen(line);
        char *numTok = strtok(line, " ");

        while (numTok)
        {
            numbers[ni++] = atoi(numTok);
            numTok = strtok(NULL, " ");
        }

        if (is_good_with_skip(numbers, ni))
        {
            goods++;
        }

        line += line_length + 1;
        line = strtok(line, "\n");
    }
    free(line);

    int result = goods;
    printf("Result is: %d\n", result);
}