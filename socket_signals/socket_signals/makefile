progetto: exe/leader exe/c1 exe/c2 exe/c3 run


bin/leader.o : src/leader.c 
	gcc -c src/leader.c -o bin/leader.o
bin/c1.o: src/c1.c
	gcc -c src/c1.c -o bin/c1.o
bin/c2.o: src/c2.c
	gcc -c src/c2.c -o bin/c2.o
bin/c3.o: src/c3.c
	gcc -c src/c3.c -o bin/c3.o

exe/c1: bin/c1.o 
	gcc bin/c1.o -o exe/c1
exe/c2: bin/c2.o 
	gcc bin/c2.o -o exe/c2

exe/c3: bin/c3.o 
	gcc bin/c3.o -o exe/c3

exe/leader : bin/leader.o
	gcc bin/leader.o -o exe/leader
run : exe/leader
	./exe/leader





