CC = gcc
FLAGS=-Wall

all: main1
	
main1: frequency.o 
	$(CC) $(FLAGS) frequency.o -o frequency
	
frequency.o: frequency.c
	$(CC) $(FLAGS) -c frequency.c -o frequency.o
	
.PHONY: clean all 


clean:
	rm -f main *.o frequency
