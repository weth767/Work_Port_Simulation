main: main.o	queue.o	stack.o	keyboard.o	save.o
	gcc main.o	queue.o	stack.o	keyboard.o	save.o -o exe
	rm *.o
main.o:	main.c
	gcc -c main.c
stack.o:	stack.h	stack.c	
	gcc -c stack.c 
queue.o: queue.h	queue.c 
	gcc -c queue.c
keyboard.o:	keyboard.c keyboard.h
	gcc -c keyboard.c
save.o:	save.c	save.h
	gcc -c save.c
