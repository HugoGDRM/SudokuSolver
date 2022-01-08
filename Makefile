CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic

OBJS = solver.o sudoku.o
BIN = solver

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS) -lm

clean:
	$(RM) $(BIN) $(OBJS)
