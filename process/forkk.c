#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[]){
   switch (fork()) {
   case 0:
     printf("child\n");
     _exit(1);
   default:
     printf("parent\n");
     wait(NULL); /* Wait for child to terminate */
    break;
 }
    return 0;
}
