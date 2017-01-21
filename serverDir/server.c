#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <linux/sysctl.h>
#include <sys/syscall.h>

#include "../configDir/connection.h"

#define MAX_CONNECTION 5
#define CHILD 0
#define STRING_MAX 100

void send_update_kern_para(int connfd) {

	struct __sysctl_args args;
		
	int name[] = { CTL_KERN, KERN_NODENAME };
	int name_len = sizeof(name)/sizeof(name[0]);
//	char oldval[STRING_MAX];
//	size_t oldlen;
	char newval[] = "GirishB";
	size_t newlen;
	
	int retval;
	
/*	memset(newval, '\0', STRING_MAX);
	printf("Enter New value :: ");
	scanf(" %s", newval);
*/
	newlen = strlen(newval);

	memset(&args, 0, sizeof(struct __sysctl_args));
	args.name = name;
	args.nlen = name_len;
//	args.oldval = oldval;
//	args.oldlenp = &oldlen;
	args.newval = newval;
	args.newlen = newlen;
	
	printf(" %d %d\n", args.name[0], args.name[1]);
	
	retval = send(connfd, &args, sizeof(args), 0);
	CHECK_ERROR((retval < 0), "Send");
}
	
int main(int argv, char* argc[])
{
	int sockfd, connfd, retval;
	char buff[BUFSIZE];
	struct sockaddr_in servAddr, clientAddr;
	socklen_t servLen, clientLen;
	struct __sysctl_args arga;	

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

//		pid = fork();
//		if(pid == CHILD) {
			printf("+1 is Connnected\n");	
		/*	while (1) {
				memset(buff, '\0', BUFSIZE);
                                printf("Me :: ");
                                scanf(" %[^\n]", buff);
                                retval = send(connfd, buff, strlen(buff), 0);

				memset(buff, '\0', BUFSIZE);
				retval = recv(connfd, buff, BUFSIZE, 0);
				printf("User ::  %s\n", buff);	
			}
		*/
			send_update_kern_para(connfd);
//		}
	} while(1);
	return 0;
}
