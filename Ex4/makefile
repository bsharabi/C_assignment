FLAGS =-Wall -g
CC = gcc #if we want to change compiler

all: graph 

graph:main.o libclass.a
	$(CC) $(FLAGS) -o graph main.o graph.o minHeap.o

main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c 

libclass.a:minHeap.o graph.o
	ar -rcs libclass.a minHeap.o graph.o

graph.o: graph.c graph.h 
	$(CC) $(FLAGS) -c graph.c 

minHeap.o: minHeap.c minHeap.h 
	$(CC) $(FLAGS) -c minHeap.c 




.PHONY: clean
clean:
	rm -f *.o *.a *.so graph
run:
	./graph