#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>


#define PORT "69"

struct addrinfo *get_prog(char *servername){
	struct addrinfo hints;
	int s;
	struct addrinfo *result=NULL;
	memset(&hints,0,sizeof(hints));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = IPPROTO_UDP;  
    /*hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;*/
    s = getaddrinfo(servername, PORT, &hints, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}
    return result;
}

int main(int argc, char* argv[]){
	int sock;
	struct addrinfo * server = get_prog(argv[1]);
	if((sock = socket( AF_INET , SOCK_STREAM, 0 ))< 0) {
		perror("socket error") ;
		exit( EXIT_FAILURE );
	}
	int len;;
	sendto(sock,
	"hello",
	strlen(hello),
	MSG_CONFIRM,server,&len);
	close(sock);
	return EXIT_SUCCESS;
}
