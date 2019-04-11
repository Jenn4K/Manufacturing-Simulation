objects=main.o sem.o sharedMem.o functions.o Queue.o
project: $(objects)
	gcc $(objects) -o project
main.o : functions.h
sem.o : sem.h
sharedMem.o: sharedMem.h
Queue.o: Queue.h
functions.o: sem.h sharedMem.h Queue.h functions.h
clean:
	rm project $(objects)
