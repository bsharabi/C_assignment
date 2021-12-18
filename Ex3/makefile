FLAGS =-Wall -g
CC = gcc #if we want to change compiler

all: stringProg

stringProg:main.o libclass.a 
	$(CC) $(FLAGS) -o stringProg main.o libclass.a

main.o: main.c sequences.h
	$(CC) $(FLAGS) -c main.c 

libclass.a:Sequences.o
	ar -rcs libclass.a Sequences.o


Sequences.o: Sequences.c sequences.h
	$(CC) $(FLAGS) -c Sequences.c 	


.PHONY: clean
clean:
	rm -f *.o *.a *.so stringProg
run:
	./stringProg