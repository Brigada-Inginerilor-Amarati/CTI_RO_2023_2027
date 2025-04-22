CC = gcc

CFLAGS = -Wall -Wextra

TARGETS = client.c lista.c

HEADERS = lista.h

EXECUTABLE = exe

DYN = valgrind

all: $(TARGETS) $(HEADERS)
	clear
	$(CC) $(CFLAGS) -c lista.c
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(TARGETS)
	rm -f *.o
	$(DYN) ./$(EXECUTABLE)