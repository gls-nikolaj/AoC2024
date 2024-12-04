#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../helpers/helpers.h"

void part_1(char **input);
void part_2(char **input);

int main()
{
    printf("merry christmas!\n");

    char **input1 = read_input_lines("input.txt");
    // char **input2 = malloc(sizeof(char) * strlen(input1));
    // input2 = strdup(input1);

    part_1(input1);
    part_2(input1);

    return 0;
}

void part_1(char **input)
{
    printf("Part 1:\n");

    int result = 0;

    int width = strlen(*input);
    int height = width; // assume square

    // scan horizontally
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width - 3; x++)
        {
            char xmas[4] = {input[y][x], input[y][x + 1], input[y][x + 2], input[y][x + 3]};

            if (strncmp(xmas, "XMAS", 4) == 0)
            {
                result++;
                printf("XMAS found HZ at (%d, %d)\n", x, y);
                
            }

            if (strncmp(xmas, "SAMX", 4) == 0)
            {
                result++;
                printf("SAMX found HZ at (%d, %d)\n", x, y);

            }
        }
    }

    // scan vertically
    for (int y = 0; y < height - 3; y++)
    {
        for (int x = 0; x < width; x++)
        {
            char xmas[4] = {input[y][x], input[y + 1][x], input[y + 2][x], input[y + 3][x]};

            if (strncmp(xmas, "XMAS", 4) == 0)
            {
                result++;
                printf("XMAS found VT at (%d, %d)\n", x, y);
            }

            if (strncmp(xmas, "SAMX", 4) == 0)
            {
                result++;
                printf("SAMX found VT at (%d, %d)\n", x, y);

            }
        }
    }

    // scan diagonally, TL->BR
    for (int y = 0; y < height - 3; y++)
    {
        for (int x = 0; x < width - 3; x++)
        {
            char xmas[4] = {input[y][x], input[y + 1][x + 1], input[y + 2][x + 2], input[y + 3][x + 3]};

            if (strncmp(xmas, "XMAS", 4) == 0)
            {
                result++;
                printf("XMAS found TL-BR at (%d, %d)\n", x, y);

            }

            if (strncmp(xmas, "SAMX", 4) == 0)
            {
                result++;
                printf("SAMX found TL-BR at (%d, %d)\n", x, y);
            }
        }
    }

    // scan diagonally, TR->BL
    for (int y = 0; y < height - 3; y++)
    {
        for (int x = 3; x < width; x++)
        {
            char xmas[4] = {input[y][x], input[y + 1][x - 1], input[y + 2][x - 2], input[y + 3][x - 3]};

            if (strncmp(xmas, "XMAS", 4) == 0)
            {
                result++;
                printf("XMAS found TR-BL at (%d, %d)\n", x, y);

            }

            if (strncmp(xmas, "SAMX", 4) == 0)
            {
                result++;
                printf("SAMX found TR-BL at (%d, %d)\n", x, y);

            }
        }
    }

    printf("Result is: %d\n", result);
}

void part_2(char **input)
{
    printf("Part 2:\n");

    int result = 0;

    int width = strlen(*input);
    int height = width; // assume square

    // scan diagonally
    for (int y = 0; y < height - 2; y++)
    {
        for (int x = 0; x < width - 2; x++)
        {
            char x_mas[5] = {input[y][x], input[y + 1][x + 1], input[y + 2][x + 2], input[y][x+2], input[y+2][x]};

            if (strncmp(x_mas, "MASMS", 5) == 0)
            {
                result++;
                printf("X-MAS found at (%d, %d)\n", x, y);
            }

            if (strncmp(x_mas, "SAMMS", 5) == 0)
            {
                result++;
                printf("X-MAS found at (%d, %d)\n", x, y);
            }

            if (strncmp(x_mas, "MASSM", 5) == 0)
            {
                result++;
                printf("X-MAS found at (%d, %d)\n", x, y);
            }

            if (strncmp(x_mas, "SAMSM", 5) == 0)
            {
                result++;
                printf("X-MAS found at (%d, %d)\n", x, y);
            }

            // if (strncmp(xmas, "SAMX", 3) == 0)
            // {
            //     result++;
            //     printf("SAMX found TL-BR at (%d, %d)\n", x, y);
            // }
        }
    }

    printf("Result is: %d\n", result);
}