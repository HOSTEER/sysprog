#enseash : main.o REPL.o signal.o
#	gcc -o enseash main.o REPL.o signal.o
#main.o : main.c
#	gcc -c -Wall main.c -g
#REPL.o : REPL.c
#	gcc -c -Wall REPL.c -g
#signal.o : signal.c
#	gcc -c -Wall signal.c -g

client : client.o
	gcc -o client client.o

client.o : client.c
	gcc -c -Wall client.c -g


