#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "REPL.h"
#include <sys/types.h>
#include <sys/wait.h>
#define PROMPT "enseash %"
#define BUFFERSIZE 10

int main(int argc, char* argv[]){
	char msgAcceuil[]="Bienvenue dans le Shell ENSEA.\n\rPour quitter, tapez 'exit'.\n\renseash %";
	write(STDOUT_FILENO, msgAcceuil, sizeof(msgAcceuil));
	char buffer[BUFFERSIZE];
	int stat=1;
	while(read(STDOUT_FILENO, buffer , BUFFERSIZE)) /* break with ^D or ^Z */
	{	
		//stat=interpretor(buffer);
		/*if(stat==0){
			break;
		}else{
			write(1, PROMPT, sizeof(PROMPT));
		}*/
		int pid;
		pid=fork();
		if(pid==0){
			execlp(buffer, buffer,NULL);
			return (EXIT_FAILURE);
		}
		else{
			wait(NULL);
			write(STDOUT_FILENO,PROMPT,strlen(PROMPT));
		}
	}
	/*if(stat!=0){
		write(1, "\n", sizeof("\n"));
	}*/
	return EXIT_SUCCESS;
}
