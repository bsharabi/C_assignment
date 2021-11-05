FLAGS =-Wall -g
CC = gcc #if we want to change compiler
all: recursived recursives loopd loops mains maindloop maindrec

#static
mains: main.o libclassrec.a 
	$(CC) $(FLAGS) -o mains main.o libclassrec.a -lm
#dynamic
maindloop:main.o 
	$(CC) $(FLAGS) -o maindloop main.o ./libclassloops.so -lm
#dynamic
maindrec:main.o 
	$(CC) $(FLAGS) -o maindrec main.o ./libclassrec.so -lm
#create static lib
loops: libclassloops.a
#create static lib
recursives:libclassrec.a
#create dynamic lib
recursived:libclassrec.so
#create dynamic lib
loopd:libclassloops.so

libclassloops.a:basicClassification.o advancedClassificationLoop.o 
	ar -rcs libclassloops.a basicClassification.o advancedClassificationLoop.o
libclassrec.a:basicClassification.o advancedClassificationRecursion.o
	ar -rcs libclassrec.a basicClassification.o advancedClassificationRecursion.o  
libclassrec.so:basicClassification.o advancedClassificationRecursion.o
	$(CC) $(FLAGS) -shared -o libclassrec.so basicClassification.o advancedClassificationRecursion.o
libclassloops.so:basicClassification.o advancedClassificationLoop.o
	$(CC) $(FLAGS) -shared -o libclassloops.so basicClassification.o advancedClassificationLoop.o

basicClassification.o: basicClassification.c NumClass.h
	$(CC) $(FLAGS) -c basicClassification.c 
advancedClassificationRecursion.o: advancedClassificationRecursion.c NumClass.h
	$(CC) $(FLAGS) -c advancedClassificationRecursion.c 
advancedClassificationLoop.o: advancedClassificationLoop.c NumClass.h
	$(CC) $(FLAGS) -c advancedClassificationLoop.c 

main.o: main.c NumClass.h
	$(CC) $(FLAGS) -c main.c 
	
#.PHONY means that clean is not a file.	
.PHONY: clean
clean:
	rm -f *.o *.a *.so mains maindloop maindrec