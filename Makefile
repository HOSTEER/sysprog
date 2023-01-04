enseash : main.o REPL.o
	gcc -o enseash main.o REPL.o
main.o : main.c
	gcc -c -Wall main.c -g
REPL.o : REPL.c
	gcc -c -Wall REPL.c -g

