#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include "../configDir/connection.h"

int main(int argc, char* argv[]) {

	int sockfd, retval;
	struct sockaddr_in servAddr;
	socklen_t servLen;
	char buff[BUFSIZE];
	if(argv[1] == NULL) {
		printf("Invalid network address \"%s\"\n", argv[1]);
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	CHECK_ERROR((sockfd < 0), "Socket");

	bzero(&servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT_NUMBER);
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);

	servLen = sizeof(servAddr);
	retval = connect(sockfd, (struct sockaddr *)&servAddr, servLen);
	CHECK_ERROR((retval < 0), "Connect");

	do {
		memset(buff, '\0' , BUFSIZE);
		retval = recv(sockfd, buff, BUFSIZE, 0);
                printf("Computer :: %s\n", buff);

		memset(buff, '\0' , BUFSIZE);
		printf("Me :: ");
		scanf(" %[^\n]", buff);
		retval = send(sockfd, buff, strlen(buff), 0);
	} while(1);

	printf("connection establisted\n");

	return 0;
}
