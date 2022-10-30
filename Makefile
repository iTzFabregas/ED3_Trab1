all: main.o funcoesDadas.o open_close.o command1.o command2.o command3.o command4.o command5.o command6.o register.o print_msg.o write_func.o
	gcc -o trab1 main.o funcoesDadas.o open_close.o command1.o command2.o command3.o command4.o command5.o command6.o register.o print_msg.o write_func.o

run:
	@./trab1

main.o: main.c
	gcc -o main.o -c main.c

funcoesDadas.o: funcoesDadas.c
	gcc -o funcoesDadas.o -c funcoesDadas.c

open_close.o: open_close.c
	gcc -o open_close.o -c open_close.c

print_msg.o: print_msg.c
	gcc -o print_msg.o -c print_msg.c
	
register.o: register.c
	gcc -o register.o -c register.c

command1.o: command1.c
	gcc -o command1.o -c command1.c

command2.o: command2.c
	gcc -o command2.o -c command2.c	

command3.o: command3.c
	gcc -o command3.o -c command3.c

command4.o: command4.c
	gcc -o command4.o -c command4.c

command5.o: command5.c
	gcc -o command5.o -c command5.c

command6.o: command6.c
	gcc -o command6.o -c command6.c

write_func.o: write_func.c
	gcc -o write_func.o -c write_func.c

copy:
	rm *.bin
	cp antes/* ./

clean:
	rm trab1 *.o

zip:
	zip trab1.zip Makefile *.c *.o