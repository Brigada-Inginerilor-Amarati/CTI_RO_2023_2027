CC = gcc

CFLAGS = -Wall

TARGETS = fotbal.o client.o 

HEADERS = fotbal.h

EXECUTABLE = exe

LEAKS = valgrind

all : $(TARGETS) $(HEADERS)
	clear
	$(CC) $(CFLAGS) -c fotbal.c
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(TARGETS)
	rm -f *.o
	$(LEAKS) ./$(EXECUTABLE)
