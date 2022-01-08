#ifndef SUDOKU_H
#define SUDOKU_H

#include <stddef.h>

typedef struct Sudoku
{
    size_t edge;
    size_t *grid;
} Sudoku;

size_t get(Sudoku *sudoku, size_t x, size_t y);
void put(Sudoku *sudoku, size_t x, size_t y, size_t value);
void print_sudoku(Sudoku *sudoku);
Sudoku *get_sudoku_from_file(char *pathname, size_t size);
void delete_sudoku(Sudoku *sudoku);

#endif
