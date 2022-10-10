all:
	gcc -o comando2.o -c comando2.c
	gcc -o main.o -c main.c
	gcc -o trab1 comando2.o main.o

run:
	./trab1