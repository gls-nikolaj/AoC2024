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

    // part_1(input1);
    part_2(input2);

    return 0;
}

struct block
{
    int file_id;    // -1 = empty
    int file_subid; // number chunk of file
} typedef block_t;

struct file
{
    block_t *blocks;
    int size;      // number of blocks
    bool reserved; // is the space reserved for a file, or free
} typedef file_t;

struct disk
{
    file_t *files;
    int size; // number of files
} typedef disk_t;

struct node2
{
    int file_id;
    int offset;
    int size;
} typedef node2_t;

struct disk2
{
    node2_t *nodes;
    int size;
} typedef disk2_t;

bool is_fragmented(disk_t disk)
{

    bool free_space_found = false;
    for (int i = 0; i < disk.size; i++)
    {
        for (int j = 0; j < disk.files[i].size; j++)
        {

            if (disk.files[i].blocks[j].file_id == -1 && !free_space_found)
            {
                free_space_found = true;
            }

            if (disk.files[i].blocks[j].file_id > -1 && free_space_found)
            {
                return true;
            }
        }
    }

    return false;
}

disk_t
parse_disk_image(char *input)
{

    // 00...111...2...333.44.5555.6666.777.888899
    bool is_file = true;
    int file_id = 0;

    unsigned int blocks_count = 16;

    file_t *files = calloc(0, sizeof(file_t));
    disk_t disk = {
        .files = files,
        .size = 0,
    };

    while (*input)
    {
        char chr[1];
        strncpy(chr, input, 1);

        file_t *tmpf = _recalloc(disk.files, sizeof(file_t), ++disk.size); // allocate for another file
        if (tmpf == NULL)
        {
            free(disk.files);
            exit(EXIT_FAILURE);
        }
        disk.files = tmpf;

        int csz = atoi(chr);                           // check new file size
        block_t *tmpb = malloc(csz * sizeof(block_t)); // allocate file blocks
        if (tmpb == NULL)
        {
            exit(EXIT_FAILURE);
        }

        disk.files[disk.size - 1].blocks = tmpb;
        disk.files[disk.size - 1].size = csz;

        if (is_file)
        {
            disk.files[disk.size - 1].reserved = true;

            for (int i = 0; i < csz; i++)
            {
                block_t b = {
                    .file_id = file_id,
                    .file_subid = i,
                };
                disk.files[disk.size - 1].blocks[i] = b;
            }

            file_id++;
        }
        else
        {
            disk.files[disk.size - 1].reserved = false;

            for (int i = 0; i < csz; i++)
            {
                block_t b = {
                    .file_id = -1,
                    .file_subid = -1,
                };
                disk.files[disk.size - 1].blocks[i] = b;
            }
        }

        is_file = !is_file;
        input++;
    }

    return disk;
}

disk2_t
parse_disk_image_v2(char *input)
{

    // 00...111...2...333.44.5555.6666.777.888899
    bool is_file = true;
    int file_id = 0;

    node2_t *nodes = calloc(0, sizeof(node2_t));
    disk2_t disk = {
        .nodes = nodes,
        .size = 0,
    };

    while (*input)
    {
        char chr[1];
        strncpy(chr, input, 1);

        node2_t *tmpf = _recalloc(disk.nodes, sizeof(node2_t), ++disk.size); // allocate for another file
        if (tmpf == NULL)
        {
            free(disk.nodes);
            exit(EXIT_FAILURE);
        }
        disk.nodes = tmpf;

        int csz = atoi(chr); // check new file size

        disk.nodes[disk.size - 1].offset = disk.size - 1;
        disk.nodes[disk.size - 1].size = csz;

        if (is_file)
        {
            disk.nodes[disk.size - 1].file_id = file_id++;
        }
        else
        {
            disk.nodes[disk.size - 1].file_id = -1;
        }

        is_file = !is_file;
        input++;
    }

    return disk;
}

unsigned long long
calculate_checksum_v1(disk_t disk)
{
    unsigned long long checksum = 0;
    int pos = 0;
    for (int i = 0; i < disk.size; i++)
    {
        for (int j = 0; j < disk.files[i].size; j++)
        {
            if (disk.files[i].blocks[j].file_id == -1)
                continue;

            checksum += pos++ * disk.files[i].blocks[j].file_id;
        }
    }

    return checksum;
}

unsigned long long
calculate_checksum_v2(disk2_t disk)
{
    unsigned long long checksum = 0;
    int pos = 0;
    for (int i = 0; i < disk.size; i++)
    {
        if (disk.nodes[i].file_id == -1)
        {
            for (int j = 0; j < disk.nodes[i].size; j++)
            {
                pos++;
            }

            continue;
        }

        for (int j = 0; j < disk.nodes[i].size; j++)
        {
            checksum += pos++ * disk.nodes[i].file_id;
        }
    }

    return checksum;
}

void print_blocks(disk_t disk)
{
    for (size_t i = 0; i < disk.size; i++)
    {
        for (size_t j = 0; j < disk.files[i].size; j++)
        {

            if (disk.files[i].blocks[j].file_id != -1)
                printf("%d", disk.files[i].blocks[j].file_id);
            else
                printf(".");
        }
    }

    printf("\n");
    fflush(stdout);
}

void print_blocks_v2(disk2_t disk)
{
    for (size_t i = 0; i < disk.size; i++)
    {
        for (size_t j = 0; j < disk.nodes[i].size; j++)
        {
            if (disk.nodes[i].file_id != -1)
                printf("%d", disk.nodes[i].file_id);
            else
                printf(".");
        }
    }

    printf("\n");
    fflush(stdout);
}

void part_1(char *input)
{
    printf("Part 1:\n");

    disk_t disk = parse_disk_image(input);
    print_blocks(disk);

    while (is_fragmented(disk)) // iterate lines
    {
        // Get right most block and erase it
        block_t right_most;
        for (int i = disk.size - 1; i >= 0; i--)
        {
            for (int j = disk.files[i].size - 1; j >= 0; j--)
            {
                if (disk.files[i].blocks[j].file_id != -1)
                {
                    right_most = disk.files[i].blocks[j];
                    disk.files[i].blocks[j] = (block_t){
                        .file_id = -1,
                        .file_subid = 0,
                    };
                    goto break_first;
                }
            }
        }
    break_first:

        // Get first free and insert
        for (int i = 0; i < disk.size; i++)
        {
            for (int j = 0; j < disk.files[i].size; j++)
            {
                if (disk.files[i].blocks[j].file_id == -1)
                {
                    disk.files[i].blocks[j] = right_most;
                    goto break_second;
                }
            }
        }
    break_second:

        print_blocks(disk);
    }

    // for (size_t i = 0; i < disk.size; i++)
    // {
    //     if (disk.blocks[i].file_id != -1)
    //         printf("%d", disk.blocks[i].file_id);
    //     else
    //         printf(".");
    // }
    // printf("\n");
    // fflush(stdout);

    unsigned long long result = calculate_checksum_v1(disk);

    for (int i = 0; i < disk.size; i++)
    {
        free(disk.files[i].blocks);
    }
    free(disk.files);

    // example: 1928
    printf("Result is: %llu\n", result);
}

void part_2(char *input)
{
    printf("Part 2:\n");

    disk2_t disk = parse_disk_image_v2(input);
    // print_blocks_v2(disk);

    bool file_moved = false;
    // while (file_moved) // iterate lines
    {
        for (size_t k = 1; k < disk.size; k++)
        {

            qsort(disk.nodes, disk.size, sizeof(node2_t), comp_node2);

            if (file_moved)
            {
                // print_blocks_v2(disk);
                //k = 1;
            }

            file_moved = false;

            // Get right most block and erase it - move further left each time
            node2_t *right_most;
            for (int i = disk.size - k; i >= 0; i--)
            {
                if (disk.nodes[i].file_id != -1)
                {
                    right_most = &disk.nodes[i];
                    goto break_first;
                }
            }
        break_first:
            (void)0;

            // Get first free and insert
            for (int i = 0; i < disk.size; i++)
            {
                if (disk.nodes[i].file_id == -1 && disk.nodes[i].size >= right_most->size && disk.nodes[i].offset < right_most->offset)
                {
                    int excess_blocks = disk.nodes[i].size - right_most->size;

                    // update destination file
                    disk.nodes[i] = *right_most;
                    disk.nodes[i].offset = i;

                    // update source file
                    right_most->file_id = -1;

                    // move excess (if any) free memory
                    if (excess_blocks > 0)
                    {
                        node2_t *new_fragment = malloc(sizeof(node2_t));
                        new_fragment->offset = i + 1;
                        new_fragment->size = excess_blocks;
                        new_fragment->file_id = -1;

                        disk.nodes = _recalloc(disk.nodes, ++disk.size, sizeof(node2_t));
                        disk.nodes[disk.size - 1] = *new_fragment;

                        // create a new node of file_id = -1 with a size of excess_blocks and insert at disk.nodes[i+1]
                        for (int j = i + 1; j < disk.size - 1; j++)
                        {
                            disk.nodes[j].offset++;
                        }
                    }

                    file_moved = true;
                    // print_blocks_v2(disk);
                    goto break_second;
                }
            }

        break_second:
            (void)0;

            // print_blocks(disk);
        }
    }

    // 00992111777.44.333....5555.6666.....8888..
    // print_blocks_v2(disk);

    unsigned long long result = calculate_checksum_v2(disk);
    free(disk.nodes);

    // example: 2858
    printf("Result is: %llu\n", result);
}