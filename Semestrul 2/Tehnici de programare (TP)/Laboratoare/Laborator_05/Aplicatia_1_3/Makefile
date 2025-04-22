CC = gcc
CFLAGS = -Wall 
TARGETS = client.c hs_utils.c
HEADERS = hs_utils.h
EXECUTABLE = exe

all: $(TARGETS) $(HEADERS)
	clear
	$(CC) $(CFLAGS) -c hs_utils.c
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(TARGETS)
	rm -f *.o
	./$(EXECUTABLE)