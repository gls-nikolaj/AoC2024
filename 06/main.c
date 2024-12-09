#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../helpers/helpers.h"

void part_1(char **input);
void part_2(char **input);

int main()
{
    printf("merry christmas!\n");

    char **input1 = read_input_lines("input.example.txt");
    // char *input2 = malloc(sizeof(char) * strlen(input1));
    // input2 = strdup(input1);

    part_1(input1);
    // part_2(input2);

    return 0;
}

struct pos
{
    int x;
    int y;
} typedef pos_t;

enum direction
{
    d_north,
    d_east,
    d_south,
    d_west,
} typedef direction_t;

int solve_path(char **input, int map_width, int map_height, pos_t from, direction_t dir, int moves)
{

    int xmod = 0;
    int ymod = 0;
    switch (dir)
    {
    case d_north:
        ymod = -1;
        break;
    case d_east:
        xmod = 1;
        break;
    case d_south:
        ymod = 1;
        break;
    case d_west:
        xmod = -1;
        break;
    default:
        exit(EXIT_FAILURE);
    }

    bool obstacle_hit = false;
    direction_t next_direction = (direction_t)((dir + 1) % 4);
    if (dir == d_north || dir == d_south)
    {
        for (int y = from.y; y < map_height && y >= 0; y += ymod)
        {
            // printf("moving to (%d, %d)\n", from.x, y);
            if (input[y][from.x] == '#')
            {
                printf("obstacle hit at (%d, %d)\n", from.x, y);
                obstacle_hit = true;
                break;
            } 
            else if(input[y][from.x] != 'X')
            {
                input[y][from.x] = 'X';
                from.y = y;
                moves++;
            }

        }
    }
    else
    {
        for (int x = from.x; x < map_width && x >= 0; x += xmod)
        {
            // printf("moving to (%d, %d)\n", x, from.y);
            if (input[from.y][x] == '#')
            {
                printf("obstacle hit at (%d, %d)\n", x, from.y);
                obstacle_hit = true;
                break;
            }
            else if( input[from.y][x] != 'X')
            {
                input[from.y][x] = 'X';
                from.x = x;
                moves++;
            }
        }
    }
    printf("moves thus far: %d\n", moves);

    fflush(stdout);
    if (!obstacle_hit) // out of map
    {
        printf("guard left map at (%d, %d) after %d visited cells\n", from.x, from.y, moves);
        return moves;
    }

    return solve_path(input, map_width, map_height, from, next_direction, moves);
}

// 1,4
// 1,9
// 6,8
void part_1(char **input)
{
    printf("Part 1:\n");

    int result = 0;

    int width = strlen(*input);
    int height = width; // squares ftw

    printf("map is %d by %d\n", width, height);

    pos_t pos = {
        .x = 0,
        .y = 0};

    // Find guard
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (input[y][x] == '^')
            {
                pos.x = x;
                pos.y = y;
                break;
            }
        }
    }

    printf("guard starts at (%d, %d)\n", pos.x, pos.y);
    // iterate path
    result = solve_path(input, width, height, pos, d_north, 0);
    
    int x_count = 0;
    for(int i = 0; i < width; i++) 
    {
        char *line = input[i];
        while(*line) 
        {
            if(*(line++) == 'X') 
            {
                x_count++;
            }
        }
    }

    // 4926 = too high
    printf("Result is: %d, maybe %d\n", result, x_count);
}

void part_2(char **input)
{
    printf("Part 2:\n");

    int result = 0;
    printf("Result is: %d\n", result);
}