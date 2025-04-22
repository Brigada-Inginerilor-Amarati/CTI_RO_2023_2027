CC = gcc

CFLAGS = -Wall

TARGETS = p_queue.o client.o 

HEADERS = p_queue.h

EXECUTABLE = exe

all : $(TARGETS) $(HEADERS)
	clear
	$(CC) $(CFLAGS) -c p_queue.c
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(TARGETS)
	rm -f *.o
	./$(EXECUTABLE)
