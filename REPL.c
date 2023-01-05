#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define PROMPT "enseash %"

int interpretor(char * buffer){
	if(strcmp(buffer,"exit\n")==0){
		return 0;
	}/*else if(strcmp(buffer,"ls\n")==0){
		struct stat s;
	}*/
	else{
		return 1;
	}
	/*int pid;
	pid=fork();
	if(pid==0){
		execlp(buffer, buffer,NULL);
		return (EXIT_FAILURE);
	}
	else{
		wait(NULL);
		write(STDOUT_FILENO,PROMPT,strlen(PROMPT));
	}*/
}
