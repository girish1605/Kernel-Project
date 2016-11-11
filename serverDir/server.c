#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../configDir/connection.h"

#define MAX_CONNECTION 5
#define CHILD 0

int main(int argv, char* argc[])
{
	int sockfd, connfd, retval;
	char buff[BUFSIZE];
	struct sockaddr_in servAddr, clientAddr;
	socklen_t servLen, clientLen;

	/* Create Socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	CHECK_ERROR((sockfd < 0), "Socket");	

	/* Bind Socket */
	bzero(&servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT_NUMBER);
	servAddr.sin_addr.s_addr = INADDR_ANY;

	retval = bind(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr));
	CHECK_ERROR((retval < 0), "Bind");
	
	/* Listen */
	retval = listen(sockfd, MAX_CONNECTION);
	CHECK_ERROR((retval < 0), "Listen");
	
	do {
		pid_t pid;
		clientLen = sizeof(clientAddr);
		connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientLen);
		CHECK_ERROR((connfd < 0), "Accept");		

		pid = fork();
		if(pid == CHILD) {
			printf("Yey! Client Connected\n");
			printf("Client's ip : port >> %s : %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));	
			while (1) {
				memset(buff, '\0', BUFSIZE);
                                printf("Me :: ");
                                scanf(" %[^\n]", buff);
                                retval = send(connfd, buff, strlen(buff), 0);

				memset(buff, '\0', BUFSIZE);
				retval = recv(connfd, buff, BUFSIZE, 0);
				printf("User ::  %s\n", buff);
			}
		}
	} while(1);

	return 0;
}
