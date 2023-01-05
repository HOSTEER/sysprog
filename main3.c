//#inlcude "question3.h

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define MAX 200
#define MIN 28
#define PROMPT "enseash %"
#define MESSAGE "Bienvenue dans le Shell ENSEA.\n\rPour quitter, tapez 'exit'.\n"
#define EXIT_MSG "bye bye...\n"

void clean(char * buf){
	while(*buf!='\0'){
		*buf='\0';
		buf++;
	}
}

int main(){
	char Commande[MAX];
	int pid;
	struct timespec start, stop;
	double dif;
	
	write(STDOUT_FILENO,MESSAGE,strlen(MESSAGE));
	write(STDOUT_FILENO,PROMPT,strlen(PROMPT));
	while(read(STDOUT_FILENO,Commande,MAX)){
		Commande[strlen(Commande)-1]='\0';
		if(strncmp(Commande,"exit",4)==0){
			write(STDOUT_FILENO,EXIT_MSG,strlen(EXIT_MSG));
			return 0;
		}
		clock_gettime( CLOCK_REALTIME, &start);
		pid=fork();
		if(pid==0){
			execlp(Commande,Commande,NULL);
		}
		else{
			wait(NULL);
			int status;
			char sigbuf[MIN];
			clock_gettime( CLOCK_REALTIME, &stop);
			dif=(stop.tv_nsec - start.tv_nsec)/1000000;
			if(WIFEXITED(status)){
				sprintf(sigbuf,"enseash [exit:%d|%3.3fms]%\n",WEXITSTATUS(status),dif);
				write(STDOUT_FILENO,sigbuf,MIN);
				clean(sigbuf);
			}else if(WIFSIGNALED(status)){
				sprintf(sigbuf,"enseash [sign:%%d|%3.3fms]%\n",WTERMSIG(status),dif);
				write(STDOUT_FILENO,sigbuf,MIN);
				clean(sigbuf);
			}
			write(STDOUT_FILENO,PROMPT,strlen(PROMPT));
		}
	}
	write(STDOUT_FILENO,"\n",1);
	return EXIT_SUCCESS;
}
