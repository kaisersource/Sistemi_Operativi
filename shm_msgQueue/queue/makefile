progetto: start func.o sem leader c1 c2 c3


func.o: func.c func.h
	gcc -c func.c 

start: start.c func.o
	gcc start.c func.o -o start

sem: sem.c func.o
	gcc sem.c func.o -o sem

leader: leader.c func.o
	gcc leader.c func.o -o leader

c1: c1.c func.o
	gcc c1.c func.o -o c1

c2: c2.c func.o
	gcc c2.c func.o -o c2

c3: c3.c func.o
	gcc c3.c func.o -o c3
