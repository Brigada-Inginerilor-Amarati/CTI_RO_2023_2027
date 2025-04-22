CC = gcc

CFLAGS = -Wall -Wextra

TARGETS = client.c bombe.c

HEADERS = bombe.h

EXECUTABLE = exe

DYN = valgrind

FIN = in.txt

all: $(TARGETS) $(HEADERS)
	clear
	$(CC) $(CFLAGS) -c bombe.c
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(TARGETS)
	rm -f *.o
	$(DYN) ./$(EXECUTABLE) $(FIN)