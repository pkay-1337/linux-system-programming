#include <fcntl.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	int fd = open("/dev/tty", O_RDWR);
	pid_t parent = getpid();
	switch (int x = fork()){
		case 0:
			printf("I am the child - %d\n", getpid());
			printf("child process group id is %d\n", getpgrp());
			printf("child session id is %d\n", getsid(getpid()));
			printf("child - changing my process group\n");
			assert(setpgid(0,getpid()) == 0);
			printf("child process group id is %d\n", getpgrp());
			while(1){
				int i;
				while(tcgetpgrp(fd) == getpgrp()){
					printf("enter number : ");
					scanf("%d", &i);
					printf("child result = %d\n", i+10);
					printf("---------------------------------------------\n");
					printf("giving terminal to parent\n");
					tcsetpgrp(fd, parent);
				}
			}
			break;
		default:
			printf("I am the parent - %d\n", getpid());
			printf("parent process group id is %d\n", getpgrp());
			printf("parent session id is %d\n", getsid(getpid()));
			while(1){
				int i;
				while(tcgetpgrp(fd) == getpgrp()){
					printf("enter number : ");
					scanf("%d", &i);
					printf("parent result = %d\n", i+100);
					printf("---------------------------------------------\n");
					printf("giving terminal to child\n");
					tcsetpgrp(fd, x);
				}
			}
			break;
	}
	return 0;
}
