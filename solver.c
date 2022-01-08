#include "sudoku.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define UNASSIGNED 0

int is_safe(Sudoku *sudoku, size_t row, size_t column, size_t number)
{
    // Check column
    for (size_t i = 0; i < sudoku->edge; i++)
        if (get(sudoku, i, column) == number)
            return 0;

    // Check row
    for (size_t j = 0; j < sudoku->edge; j++)
        if (get(sudoku, row, j) == number)
            return 0;

    // Check current borow
    size_t square_size = sqrt(sudoku->edge);
    size_t square_row = (row / square_size) * square_size;
    size_t square_column = (column / square_size) * square_size;
    for (size_t i = square_row; i < square_row + square_size; i++)
        for (size_t j = square_column; j < square_column + square_size; j++)
            if (get(sudoku, i, j) == number)
                return 0;

    return 1;
}

int solve(Sudoku *sudoku)
{
    // Check for an unassigned position
    for (size_t i = 0; i < sudoku->edge; i++)
        for (size_t j = 0; j < sudoku->edge; j++)
            if (get(sudoku, i, j) == UNASSIGNED)
            {
                // Check safetcolumn for evercolumn posibilities
                for (size_t k = 1; k <= sudoku->edge; k++)
                {
                    if (is_safe(sudoku, i, j, k))
                    {
                        put(sudoku, i, j, k);

                        if (solve(sudoku))
                            return 1;

                        put(sudoku, i, j, UNASSIGNED);
                    }
                }

                // If no number can fit here, we are stuck
                return 0;
            }

    // There is no unassigned position, we solved it
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 3)
        fprintf(stderr, "This program needs 2 arguments:\n-the pathname of the grid\n-the size of the grid\n");

    printf("Welcome to the worst Sudoku solver columnou never have never seen.\n");

    Sudoku *sudoku = get_sudoku_from_file(argv[1], atoi(argv[2]));

    print_sudoku(sudoku);

    int result = solve(sudoku);
    if (!result)
        printf("This sudoku has no solution.\n");
    else
        print_sudoku(sudoku);

    delete_sudoku(sudoku);

    return 0;
}
