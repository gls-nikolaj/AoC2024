#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../helpers/helpers.h"

void part_1(char *input);
void part_2(char *input);

int main()
{
    printf("merry christmas!\n");

    char *input1 = read_input("input.txt");
    char *input2 = malloc(sizeof(char) * strlen(input1));
    input2 = strdup(input1);

    part_1(input1);
    part_2(input2);

    return 0;
}

bool 
is_num(char c)
{
    return c >= '0' && c <= '9';
}

void part_1(char *input)
{
    printf("Part 1:\n");

    unsigned long result = 0;

    char digit_1[4];
    char digit_2[4];
    while (1)
    {        
        memset(digit_1, 0, 4);
        memset(digit_2, 0, 4);

        input = strstr(input, "mul("); // find next `mul(`
        if(!input) break; // when no more mul's

        printf("%.13s => ", input);
        fflush(stdout);
        
        input += 4; // skip `mul(`

        int i = 0;
        while(is_num(*input) && i < 3) {
            digit_1[i++] = *input;

            input++;
        }

        if(*input++ != ',') continue; // invalid instruction

        int j = 0;
        while(is_num(*input) && j < 3) {
            digit_2[j++] = *input;

            input++;
        }

        if(*input != ')') continue; // invalid instruction
        
        int num1 = atoi(digit_1);
        int num2 = atoi(digit_2);

        printf("% 3d * % 3d => % 6d\n", num1, num2, num1 * num2);
        fflush(stdout);

        result += (num1 * num2);
    }

    // 187705165 = too low
    printf("Result is: %lu\n", result);
}

void part_2(char *input)
{
    printf("Part 2:\n");
    
    unsigned long result = 0;

    bool in_do = true;
    char digit_1[4];
    char digit_2[4];
    while (1)
    {        
        memset(digit_1, 0, 4);
        memset(digit_2, 0, 4);

        if(!input) break; // when no more mul's

        char *next_mul = strstr(input, "mul("); // find next `mul(`

        char *next_do = strstr(input, "do()");
        char *next_dont = strstr(input, "don't()");

        if(next_mul > next_dont) {

            if(!next_do && !next_mul) break;

            // ¯\_(ツ)_/¯
            input = next_do;
            if(!input)
                input = next_mul;
            else {
                input++;
                continue;
            }
        } else {
            input = next_mul;
        }

        // else if(in_do) {
        //     in_do = false;
        //     input = next_dont;
        //     continue;
        // }

        // if(!in_do) {
        //     input = next_do;
        //     in_do = true;
        //     continue;
        // }


        if(!input) break; // when no more mul's

        printf("%.13s => ", input);
        fflush(stdout);
        
        input += 4; // skip `mul(`

        int i = 0;
        while(is_num(*input) && i < 3) {
            digit_1[i++] = *input;

            input++;
        }

        if(*input++ != ',') continue; // invalid instruction

        int j = 0;
        while(is_num(*input) && j < 3) {
            digit_2[j++] = *input;

            input++;
        }

        if(*input != ')') continue; // invalid instruction
        
        int num1 = atoi(digit_1);
        int num2 = atoi(digit_2);

        printf("% 3d * % 3d => % 6d\n", num1, num2, num1 * num2);
        fflush(stdout);

        result += (num1 * num2);
    }
    
    
    // 109634158 = too low
    printf("Result is: %lu\n", result);
}