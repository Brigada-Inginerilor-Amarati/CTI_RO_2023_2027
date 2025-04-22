CC = clang
CFLAGS = -Wall -Wextra -lm -pedantic -Wconversion -I.
DEPS = student.h
FILES = main.c student.c
EXECUTABLE = exe

compile: $(FILES) $(DEPS)
	$(CC) -o $(EXECUTABLE) $(FILES) $(CFLAGS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

leaks: $(EXECUTABLE)
	leaks -q --atExit -- ./$(EXECUTABLE)
