NAME = queue_list
CC = gcc-13
CFLAGS = -fanalyzer -Wall -Wextra -Werror
SRC = $(wildcard *.c)
OBJ = $(wildcard *.o)
HEADER = $(NAME).h
EXPORT_OBJ = $(NAME).o
EXE = $(NAME).exe

all:
	clear
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)
	./$(EXE)
	cp $(EXPORT_OBJ) "/Users/paulhondola/Faculta/Tehnici de Programare/libraries/objects"
	cp $(HEADER) "/Users/paulhondola/Faculta/Tehnici de Programare/libraries/headers"

leaks: run
	leaks -q --atExit -- ./$(EXE)
