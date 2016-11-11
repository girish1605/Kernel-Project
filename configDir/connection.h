#define PORT_NUMBER 5678
#define BUFSIZE 1024

#define CHECK_ERROR(cond, msg) \
	if(cond) { perror(msg); exit(EXIT_FAILURE);}
