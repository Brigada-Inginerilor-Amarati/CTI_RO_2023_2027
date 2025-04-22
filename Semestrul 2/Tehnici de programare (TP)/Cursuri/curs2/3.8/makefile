CC = clang
CFLAGS = -Wall -Wextra -pedantic -Wconversion -lm
DEPS = products.h

FILES = main.c products.c
EXECUTABLE = exe

compile: $(FILES) $(DEPS)
	$(CC) -o $(EXECUTABLE) $(FILES) $(CFLAGS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

leaks: $(EXECUTABLE)
	leaks -q --atExit -- ./$(EXECUTABLE)
