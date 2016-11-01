#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "../configDir/connection.h"

int main(int argc, char* argv[]) {

	int sockfd, retval;
	struct sockaddr_in servAddr;
	socklen_t servLen;

	if(argv[1] == NULL) {
		printf("Invalid network address \"%s\"\n", argv[1]);
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		perror("Socket create failed");
		exit(2);
	}

	bzero(&servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT_NUMBER);
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);

	servLen = sizeof(servAddr);
	retval = connect(sockfd, (struct sockaddr *)&servAddr, servLen);
	if(retval < 0) {
		perror("Failed to connet");
		exit(3);
	}

	printf("connection establisted\n");

	return 0;
}
