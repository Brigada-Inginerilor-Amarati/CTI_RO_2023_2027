CC = clang
CFLAGS = -Wall -Wextra -pedantic -Wconversion -I.
DEPS = files.h matrix_data.h matrix_std.h matrix_block.h matrix_conversion.h matrix_operations.h matrix.h
FILES = main.c files.c matrix_std.c matrix_block.c matrix_conversion.c matrix_operations.c
EXECUTABLE = exe

compile: $(FILES) $(DEPS)
	$(CC) -o $(EXECUTABLE) $(FILES) $(CFLAGS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

leaks: $(EXECUTABLE)
	leaks -q --atExit -- ./$(EXECUTABLE)
