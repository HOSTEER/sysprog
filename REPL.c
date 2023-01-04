#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define PROMPT "enseash %"
#include <sys/types.h>
#include <sys/wait.h>

int interpretor(char * buffer){
	if(strcmp(buffer,"exit\n")==0){
		return 0;
	}/*else if(strcmp(buffer,"ls\n")==0){
		struct stat s;
	}*/
	else{
		return 1;
	}
	int pid;
	pid=fork();
	if(pid==0){
		execlp(buffer, buffer,NULL);}
	else{
		wait(NULL);
		write(STDOUT_FILENO,PROMPT,strlen(PROMPT));
	}
}
