#include "sudoku.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

size_t get(Sudoku *sudoku, size_t x, size_t y)
{
    return sudoku->grid[x * sudoku->edge + y];
}

void put(Sudoku *sudoku, size_t x, size_t y, size_t value)
{
    sudoku->grid[x * sudoku->edge + y] = value;
}

void print_sudoku(Sudoku *sudoku)
{
    for (size_t i = 0; i < sudoku->edge; i++)
    {
        for (size_t j = 0; j < sudoku->edge; j++)
            printf("%2ld", get(sudoku, i, j));
        printf("\n");
    }    
    printf("\n");
}

Sudoku *get_sudoku_from_file(char *pathname, size_t size)
{
    size_t fd = open(pathname, O_RDONLY);

    char *content = malloc(size * 2 * sizeof(char));
    size_t reading_result = read(fd, content, size * 2);
    if (reading_result != size * 2)
        fprintf(stderr, "Error while reading the file or the grid is not complete.\n");

    int closing_result = close(fd);
    if (closing_result == -1)
        fprintf(stderr, "Error while closing the file.\n");

    Sudoku *sudoku = malloc(sizeof(Sudoku));
    sudoku->edge = sqrt(size);
    sudoku->grid = malloc(size * sizeof(int));

    size_t i = 0;
    size_t y = 0;
    while (i < size && y < size * 2)
    {
        if (content[y] == '\n' || content[y] == ' ')
            y++;

        sudoku->grid[i++] = content[y++] - 48; 
    }
    free(content);

    return sudoku;
}

void delete_sudoku(Sudoku *sudoku)
{
    free(sudoku->grid);
    free(sudoku);
}
