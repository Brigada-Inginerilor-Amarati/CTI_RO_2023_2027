CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic

TARGETS = client.c coada.c

HEADERS = coada.h

EXECUTABLE = exe

all: $(TARGETS) $(HEADERS)
	clear
	$(CC) $(CFLAGS) -c coada.c
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(TARGETS)
	rm -f *.o
	./$(EXECUTABLE)