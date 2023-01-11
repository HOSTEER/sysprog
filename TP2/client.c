#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>


#define PORT "1069"

struct addrinfo *get_prog(char *servername){
	struct addrinfo hints;
	int s;
	struct addrinfo *result=NULL;
	memset(&hints,0,sizeof(hints));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = IPPROTO_UDP;  
    hints.ai_canonname = AI_CANONNAME;
    hints.ai_addr = servername;
    hints.ai_next = NULL;
    s = getaddrinfo(servername, PORT, &hints, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}
    return result;
}

int main(int argc, char* argv[]){
	int sock, sendEr, readEr, sockEr;
	char buf [20]="hello";
	struct addrinfo * server = get_prog(argv[1]);
	if((sock = socket( AF_INET , SOCK_STREAM, 0 ))< 0) {
		perror("socket error") ;
		exit( EXIT_FAILURE );
	}
	if(sockEr=connect(sock, server->ai_addr, (socklen_t) server->ai_addrlen)){
		perror("conn error") ;
		exit( EXIT_FAILURE );
	}
	//int conn=connect(int sock, struct sockaddr *serv_addr, socklen_t addrlen);
	if((sendEr=sendto(sock,buf,strlen(buf),MSG_NOSIGNAL,server->ai_addr,(socklen_t) server->ai_addrlen))<0){
		printf("%d\n",sendEr);
		perror("send error") ;
		exit( EXIT_FAILURE );
	}
	if((readEr=read(sock,buf,20))<0){
		perror("read error") ;
		exit( EXIT_FAILURE );
	}
	//printf("%s",buf);
	close(sock);
	return EXIT_SUCCESS;
}

///**
 //* The client sends the contents of a file to a tcpServer.
 //*
 //* This protocol works by sending individual CRLF and null terminated strings of length less than 256
 //* through the socket to the server.
 //*
 //* NOTE: This software was not designed for robustness, and likely contains bugs. It was my solution for a network computing university course. It should be used only a reference.
 //*
 //* Usage:
 //* ./client <server-address> <file-path>
 //* */

//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <netdb.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <sys/time.h>
//#include <time.h>

//#define LOCAL_SERVER_PORT 22
//#define LINE_MAX 256

//const char *APP_NAME;

//int open_connection(const char *server_addr);
//void close_connection(int sd);
//long int send_file(int sd, FILE *fd);
//void print_transfer_duration(struct timespec start, struct timespec end);

///**
 //* Verify command-line arguments.
 //* */
//int main(int argc, char *argv[])
//{
	//int sd;
    //FILE *fd;
    //long int bytes_read;

    //APP_NAME = argv[0];

	///* check command line args */
	//if (argc < 3) {
		//fprintf(stderr, "usage: %s <server> <filename> \n", APP_NAME);
		//exit(1);
	//}

	///* Open connection with server */
	//sd = open_connection(argv[1]);

	///* get file from arguments */
    //fd = fopen(argv[2], "r");
    //if(fd == NULL) {
        //fprintf(stderr, "%s: cannot read from file %s\n", APP_NAME, argv[2]);
        //close(sd);
        //exit(1);
    //}

    //bytes_read = send_file(sd, fd);
    //fclose(fd);
    //close(sd);

    //fprintf(stdout, "%s: bytes sent: %ld\n", APP_NAME, bytes_read);

	//return 0;
//}

///**
 //* Open a connection to the server and return descriptor for that socket.
 //* */
//int open_connection(const char *server_addr)
//{
    //int sd, rc;
    //struct sockaddr_in localAddr, servAddr;
    //struct hostent *h;

    ///* get server IP address (check if input is IP address or DNS name) */
    //h = gethostbyname(server_addr);
    //if (h == NULL) {
        //fprintf(stderr, "%s: unknown host '%s'\n", APP_NAME, server_addr);
        //exit(1);
    //}

    //servAddr.sin_family = h->h_addrtype;
    //memcpy((char *) &servAddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
    //servAddr.sin_port = htons(LOCAL_SERVER_PORT);

    ///* create socket */
    //sd = socket(AF_INET, SOCK_STREAM, 0);
    //if (sd < 0) {
        //fprintf(stderr, "%s: cannot open socket \n", APP_NAME);
        //exit(1);
    //}

    ///* bind any port number */
    //localAddr.sin_family = AF_INET;
    //localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //localAddr.sin_port = htons(0);

    //rc = bind(sd, (struct sockaddr *) &localAddr, sizeof(localAddr));
    //if (rc < 0) {
        //fprintf(stderr, "%s: cannot bind port TCP %u\n", APP_NAME, LOCAL_SERVER_PORT);
        //exit(1);
    //}

    ///* connect to server */
    //rc = connect(sd, (struct sockaddr *) &servAddr, sizeof(servAddr));
    //if (rc < 0) {
        //fprintf(stderr, "%s: cannot connect\n", APP_NAME);
        //exit(1);
    //}

    //return sd;
//}


///**
 //* Close a connection to the server. Performs closing procedures with the server before closing the socket.
 //* */
//void close_connection(int sd)
//{
    //ssize_t rc;
    //char buffer[LINE_MAX];

    ///* notify completion */
    //fprintf(stdout, "\n%s: sending end-of-connection token to server...\n", APP_NAME);
    //strcpy(buffer, "Done.\r\n");
    //rc = send(sd, buffer, strlen(buffer) + 1, 0);
    //if(rc < 0) {
        //fprintf(stderr, "%s: cannot send data\n", APP_NAME);
        //close(sd);
        //exit(1);
    //}

    ///* wait for ack */
    //fprintf(stdout, "%s: end-of-connection token sent. Waiting for ack...\n", APP_NAME);
    //memset(buffer, 0x0, LINE_MAX);
    //while(recv(sd, buffer, LINE_MAX, 0) > 0) {
        //if(!strcmp(buffer, "Bye.\r\n")) {
            //fprintf(stdout, "%s: received ack token from server. Terminating connection...\n", APP_NAME);
            //break;
        //}

        //memset(buffer, 0x0, LINE_MAX);
    //}
//}

///**
 //* Send a given file through a given socket, and return the number of bytes sent.
 //*
 //* Files with lines longer than 255 characters in length are truncated to 254 characters, and followed by line feed and
 //* null terminator, and then sent through the socket.
 //* */
//long int send_file(int sd, FILE *fd)
//{
    //ssize_t rc;
    //long int bytes_read = 0;
    //struct timespec start, end;
    //char buffer[LINE_MAX];

    ///* start clock */
    //clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    ///* send file contents */
    //while(fgets(buffer, LINE_MAX - 1, fd) != NULL) {
        ///* terminate last line with line feed if applicable */
        //if(strlen(buffer) > 0 && buffer[strlen(buffer) - 1] != '\n') {
            //buffer[strlen(buffer)] = '\n';
            //buffer[strlen(buffer) + 1] = '\0';
        //}

        //rc = send(sd, buffer, strlen(buffer) + 1, 0);
        //if (rc < 0) {
            //fprintf(stderr, "%s: cannot send data\n", APP_NAME);
            //fclose(fd);
            //close(sd);
            //exit(1);
        //}

        ///* increment data sent (length of string plus null terminator) */
        //bytes_read += strlen(buffer) + 1;

        //fprintf(stdout, "%s: data sent: %s", APP_NAME, buffer);
        //memset(buffer, 0x0, LINE_MAX);
    //}

    ///* stop clock */
    //clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    ///* notify completion */
    //close_connection(sd);

    ///* print transfer duration */
    //print_transfer_duration(start, end);

    //return bytes_read;
//}

///**
 //* Print a transfer duration to stdout. If duration is greater than 1000 microseconds, displayed in milliseconds.
 //*
 //* format: app_name: time elapsed: <n>us
 //* */
//void print_transfer_duration(struct timespec start, struct timespec end)
//{
    //long delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    //if(delta_us < 1000) {
        //fprintf(stdout, "%s: time elapsed: %ldus\n", APP_NAME, delta_us);
    //} else {
        //fprintf(stdout, "%s: time elapsed: %ldms\n", APP_NAME, delta_us / 1000);
    //}
//}
