CC = gcc

CFLAGS = -Wall

TARGETS = pixel.o client.o 

HEADERS = pixel.h

EXECUTABLE = exe

LEAKS = valgrind

MATH = -lm

all : $(TARGETS) $(HEADERS)
	clear
	$(CC) $(CFLAGS) -c pixel.c
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(TARGETS) $(MATH)
	rm -f *.o
	$(LEAKS) ./$(EXECUTABLE)
