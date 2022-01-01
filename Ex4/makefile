FLAGS =-Wall -g
CC = gcc #if we want to change compiler

all: graph 

graph:main.o libclass.a 
	$(CC) $(FLAGS) -o graph main.o libclass.a

main.o: main.c algo.h
	$(CC) $(FLAGS) -c main.c 

libclass.a:algo.o
	ar -rcs libclass.a algo.o

algo.o: algo.c algo.h
	$(CC) $(FLAGS) -c algo.c 

edges.o:edges.c edges.h
	$(CC) $(FLAGS) -c edges.c

nodes.o:nodes.c nodes.h
	$(CC) $(FLAGS) -c nodes.c

.PHONY: clean
clean:
	rm -f *.o *.a *.so graph
run:
	./graph