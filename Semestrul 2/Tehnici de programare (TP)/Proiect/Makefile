CC = gcc
CFLAGS = -Wall 
TARGETS = client.c rand_array.c
HEADERS = rand_array.h
EXECUTABLE = exe
MATH = -lm

FILE1 = vectori.txt
FILE2 = gauss.txt
FILE3 = poisson.txt

all: $(TARGETS) $(HEADERS)
	clear
	$(CC) $(CFLAGS) -c rand_array.c
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(TARGETS) $(MATH)
	rm -f *.o
	./$(EXECUTABLE) $(FILE1) $(FILE2) $(FILE3)