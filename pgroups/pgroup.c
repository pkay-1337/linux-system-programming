#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
	pid_t pgrp = getpgrp();
	printf("My process group id is %d\n", pgrp);
	printf("My process id is %d\n", getpid());
	printf("My session id is %d\n", getsid(getpid()));
	setsid();
	printf("My session id is %d\n", getsid(getpid()));
	return 0;
}

