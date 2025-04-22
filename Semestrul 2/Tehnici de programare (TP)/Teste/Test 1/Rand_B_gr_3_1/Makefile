CC = gcc

CFLAGS = -Wall -Werror

TARGETS = client.c coada.c

HEADERS = coada.h

EXECUTABLE = exe

DYNAMIC = valgrind

all : $(TARGETS) $(HEADERS)
	clear
	$(CC) $(CFLAGS) -c coada.c
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(TARGETS)
	rm -f *.o
	$(DYNAMIC) ./$(EXECUTABLE)