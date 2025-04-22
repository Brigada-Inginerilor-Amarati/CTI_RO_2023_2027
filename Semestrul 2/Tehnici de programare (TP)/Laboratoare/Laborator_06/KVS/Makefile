CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic

TARGETS = client.c kvs.c

HEADERS = kvs.h

EXECUTABLE = exe

all: $(TARGETS) $(HEADERS)
	clear
	$(CC) $(CFLAGS) -c kvs.c
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(TARGETS)
	rm -f *.o
	./$(EXECUTABLE)