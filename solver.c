#include "sudoku.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define UNASSIGNED 0

int is_safe(Sudoku *sudoku, size_t x, size_t y, size_t number)
{
    // Check column
    for (size_t i = 0; i < sudoku->edge; i++)
        if (get(sudoku, i, y) == number)
            return 0;

    // Check row
    for (size_t j = 0; j < sudoku->edge; j++)
        if (get(sudoku, x, j) == number)
            return 0;

    // Check current box
    size_t box_edge = sqrt(sudoku->edge);
    size_t box_pos_x = (x / box_edge) * box_edge;
    size_t box_pos_y = (y / box_edge) * box_edge;
    for (size_t i = box_pos_x; i < box_pos_x + box_edge; i++)
        for (size_t j = box_pos_y; j < box_pos_y + box_edge; j++)
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
                // Check safety for every posibilities
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

    printf("Welcome to the worst Sudoku solver you never have never seen.\n");

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
