CC = gcc
CFLAGS = -Wall 
TARGETS = client.c stack.c
HEADERS = stack.h
EXECUTABLE = exe

all: $(TARGETS) $(HEADERS)
	clear
	$(CC) $(CFLAGS) -c stack.c
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(TARGETS)
	rm -f *.o
	./$(EXECUTABLE)