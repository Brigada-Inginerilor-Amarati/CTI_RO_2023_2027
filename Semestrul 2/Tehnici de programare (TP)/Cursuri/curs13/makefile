NAME = floodfill
CC = gcc-14
CFLAGS = -fanalyzer -Wall -Wextra
SRC = $(wildcard *.c)
OBJ = $(wildcard *.o)
EXE = $(NAME).exe

run:
	clear
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)
	./$(EXE)

leaks: run
	leaks -q --atExit -- ./$(EXE)
