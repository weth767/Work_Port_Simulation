main: main.o	stack.o	queue.o keyboard.o
	gcc main.o stack.o queue.o keyboard.o -o exe
	rm *.o
main.o:	main.c
	gcc -c main.c
stack.o:	stack.c	stack.h
	gcc -c stack.c 
queue.o:	queue.c queue.h	
	gcc -c queue.c
keyboard.o:	keyboard.c keyboard.h
	gcc -c keyboard.c
