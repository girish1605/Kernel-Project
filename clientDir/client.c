#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <linux/sysctl.h>
#include <sys/syscall.h>

#include "../configDir/connection.h"

#define STRING_MAX 100

//int _sysctl(struct __sysctl_args * args);

void update_kern_para(int sockfd) {
	struct __sysctl_args args;
	struct kern_param new_args;	

	int retval;
	char oldval[STRING_MAX];
	size_t oldlen;
	FILE *fp = NULL;
	int sid;	

	memset(oldval, '\0', STRING_MAX);
	memset(&new_args, 0, sizeof(struct kern_param));
	memset(&args, 0, sizeof(struct __sysctl_args));	
	
	retval = recv(sockfd, &new_args, sizeof(struct kern_param), 0);
	CHECK_ERROR((retval < 0), "Receive");

	printf("%d %d | %s | %lu\n", new_args.name[0], new_args.name[1], new_args.newval, new_args.newlen);

	args.name = new_args.name;
	args.nlen = sizeof(new_args.name) / sizeof(new_args.name[0]);
	args.oldval = oldval;
	args.oldlenp = &oldlen;
	args.newval = new_args.newval;
	args.newlen = new_args.newlen;

	printf("name[0] = %d\n", args.name[0]);
	printf("name[1] = %d\n", args.name[1]);
	
	
	retval = syscall(SYS__sysctl, &args);
	CHECK_ERROR((retval == -1), "_sysctl");
	
	printf("oldval = %s | oldlen = %lu\n\
		newval = %s | newlen = %lu\n", oldval, oldlen, (char *)args.newval, args.newlen);
}

int main(int argc, char* argv[]) {
	char *ip = "127.0.0.1";
	int sockfd, retval;
	struct sockaddr_in servAddr;
	socklen_t servLen;
	char buff[BUFSIZE];
/*	if(argv[1] == NULL) {
		printf("Invalid network address \"%s\"\n", argv[1]);
		exit(1);
	}
*/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	CHECK_ERROR((sockfd < 0), "Socket");

	bzero(&servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT_NUMBER);
	servAddr.sin_addr.s_addr = inet_addr(ip);

	servLen = sizeof(servAddr);
	retval = connect(sockfd, (struct sockaddr *)&servAddr, servLen);
	CHECK_ERROR((retval < 0), "Connect");

	printf("connection establisted\n");

	update_kern_para(sockfd);	

	return 0;
}
