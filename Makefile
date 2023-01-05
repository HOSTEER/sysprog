#enseash : main.o REPL.o signal.o
#	gcc -o enseash main.o REPL.o signal.o
#main.o : main.c
#	gcc -c -Wall main.c -g
#REPL.o : REPL.c
#	gcc -c -Wall REPL.c -g
#signal.o : signal.c
#	gcc -c -Wall signal.c -g

enseash : main2.o
	gcc -o enseash main2.o

main2.o : main2.c
	gcc -c -Wall main2.c -g

#enseash : main3.o
#	gcc -o enseash main3.o

#main3.o : main3.c
#	gcc -c -Wall main3.c -g
	

