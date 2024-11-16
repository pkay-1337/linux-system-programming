#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void main(){
  int pid, sig;
  printf("MY PID : %d\n", getpid());
  printf("Enter PID : ");
  scanf("%d", &pid);
  printf("Enter SIGNAL NUMBER : ");
  scanf("%d", &sig);
  kill(pid, sig);
}
