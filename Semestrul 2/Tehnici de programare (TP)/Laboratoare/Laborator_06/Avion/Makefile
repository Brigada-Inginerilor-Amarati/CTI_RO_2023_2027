CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic

TARGETS = client.c avion.c

HEADERS = avion.h

EXECUTABLE = exe

all: $(TARGETS) $(HEADERS)
	clear
	$(CC) $(CFLAGS) -c avion.c
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(TARGETS)
	rm -f *.o
	./$(EXECUTABLE)