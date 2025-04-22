CC = gcc

CFLAGS = -Wall -Werror

TARGETS = client.c coada.c

HEADERS = coada.h

EXECUTABLE = exe

DYN = valgrind

all : $(TARGETS) $(HEADERS)
	clear
	$(CC) $(CFLAGS) -c coada.c
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(TARGETS)
	rm -f *.o
	$(DYN) ./$(EXECUTABLE)
