#include <unistd.h>
#include <stdio.h>
#include <string.h>

int interpretor(char * buffer){
	if(strcmp(buffer,"exit\n")==0){
		return 0;
	}
	else{
		return 1;
	}
}
