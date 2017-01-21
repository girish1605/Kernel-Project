#define PORT_NUMBER 5678
#define BUFSIZE 1024

#define CHECK_ERROR(cond, msg) \
	if(cond) { perror(msg); exit(EXIT_FAILURE);}

struct kern_param { 
	int name[2];
	char newval[16];
	size_t newlen;
};
