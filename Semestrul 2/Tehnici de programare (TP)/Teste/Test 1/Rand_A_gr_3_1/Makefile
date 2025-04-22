CC = gcc

CFLAGS = -Wall -Werror 

TARGETS = client.c matrice.c

HEADERS = matrice.h

EXECUTABLE = exe

all : $(TARGETS) $(HEADERS)
	clear
	$(CC) $(CFLAGS) -c matrice.c
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(TARGETS)
	rm -f *.o
	./$(EXECUTABLE)
