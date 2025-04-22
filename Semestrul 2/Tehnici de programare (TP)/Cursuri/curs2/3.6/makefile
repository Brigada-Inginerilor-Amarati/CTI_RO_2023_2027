CC = clang
CFLAGS = -Wall -Wextra -pedantic -Wconversion -lm
DEPS = objects.h

FILES = main.c objects.c
EXECUTABLE = exe

compile: $(FILES) $(DEPS)
	$(CC) -o $(EXECUTABLE) $(FILES) $(CFLAGS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

leaks: $(EXECUTABLE)
	leaks -q --atExit -- ./$(EXECUTABLE)
