#ifndef SUDOKU_H
#define SUDOKU_H

typedef struct Sudoku
{
    int edge;
    int *grid;
} Sudoku;

int get(Sudoku *sudoku, int x, int y);
void put(Sudoku *sudoku, int x, int y, int value);
void print_sudoku(Sudoku *sudoku);
Sudoku *get_sudoku_from_file(char *pathname, int size);
void delete_sudoku(Sudoku *sudoku);

#endif
