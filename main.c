#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "REPL.h"
#define BUFFERSIZE 10

int main(int argc, char* argv[]){
	char msgAcceuil[]="Bienvenue dans le Shell ENSEA.\n\rPour quitter, tapez 'exit'.\n\renseash %";
	char msgPrompt[]="enseash %";
	write(1, msgAcceuil, sizeof(msgAcceuil));
	char buffer[BUFFERSIZE];
	int stat=1;
	while(1) /* break with ^D or ^Z */
	{	
		fgets(buffer, BUFFERSIZE , stdin);
		stat=interpretor(buffer);
		if(stat==0){
			break;
		}else{
			write(1, msgPrompt, sizeof(msgPrompt));
		}
	}
}
