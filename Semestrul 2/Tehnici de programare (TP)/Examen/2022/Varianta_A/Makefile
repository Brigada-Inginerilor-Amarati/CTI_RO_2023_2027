CC = gcc

CFLAGS = -Wall

TARGETS = esantion.o client.o 

HEADERS = esantion.h

EXECUTABLE = exe

LEAKS = valgrind

all : $(TARGETS) $(HEADERS)
	clear
	$(CC) $(CFLAGS) -c esantion.c
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(TARGETS)
	rm -f *.o
	$(LEAKS) ./$(EXECUTABLE)
