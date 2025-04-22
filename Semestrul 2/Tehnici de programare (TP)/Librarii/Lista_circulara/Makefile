CC = gcc

CFLAGS = -Wall -Werror 

TARGETS = client.c lista_circulara.c

HEADERS = lista_circulara.h

EXECUTABLE = exe

all : $(TARGETS) $(HEADERS)
	clear
	$(CC) $(CFLAGS) -c lista_circulara.c
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(TARGETS)
	rm -f *.o
	./$(EXECUTABLE)
