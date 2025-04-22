CC = gcc

CFLAGS = -Wall

TARGETS = companie.o client.o 

HEADERS = companie.h

EXECUTABLE = exe

LEAKS = valgrind

all : $(TARGETS) $(HEADERS)
	clear
	$(CC) $(CFLAGS) -c companie.c
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(TARGETS)
	rm -f *.o
	$(LEAKS) ./$(EXECUTABLE)
