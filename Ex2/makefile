FLAGS =-Wall -g
CC = gcc #if we want to change compiler

all: connections

connections:main.o libclass.a 
	$(CC) $(FLAGS) -o mains main.o libclassrec.a -lm


main.o: main.c my_mat.h
	$(CC) $(FLAGS) -c main.c 

libclass.a:my_mat.o
	ar -rcs libclass.a my_mat.o


my_mat.o: my_mat.c my_mat.h
	$(CC) $(FLAGS) -c my_mat.c 	


.PHONY: clean
clean:
	rm -f *.o *.a *.so connections