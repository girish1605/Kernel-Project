#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "../configDir/connection.h"

#define MAX_CONNECTION 5

int main(int argv, char** argc)
{
	int sockfd, connfd, retval;
	char buff[BUFSIZE];
	struct sockaddr_in servAddr, clientAddr;
	socklen_t servLen, clientLen;

	/* Create Socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		perror("Failed to create socket");
		exit(1);
	}

	/* Bind Socket */
	bzero(&servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT_NUMBER);
	servAddr.sin_addr.s_addr = INADDR_ANY;

	retval = bind(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr));
	if(retval < 0) {
		perror("Failed to bind socket");
		exit(2);
	}

	/* Listen */
	retval = listen(sockfd, MAX_CONNECTION);

	if(retval < 0) {
		perror("Failed to listen");
		exit(3);
	}

	do {
		clientLen = sizeof(clientAddr);
		connfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientLen);
		if(connfd < 0) {
			perror("Failed to accept");
			exit(4);
		}

		printf("Yey! Client Connected\n");
		printf("Client's port no. :: %d\n",ntohs(clientAddr.sin_port));
	
	} while(1);

	return 0;
}
