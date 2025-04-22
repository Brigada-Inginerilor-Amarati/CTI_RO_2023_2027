CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic

TARGETS = client.c stiva.c

HEADERS = stiva.h

EXECUTABLE = exe

all: $(TARGETS) $(HEADERS)
	clear
	$(CC) $(CFLAGS) -c stiva.c
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(TARGETS)
	rm -f *.o
	./$(EXECUTABLE)