#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void main(){
  int pid, sig;
  union sigval u;
  printf("MY PID : %d\n", getpid());
  printf("Enter PID : ");
  scanf("%d", &pid);
  printf("Enter SIGNAL NUMBER : ");
  scanf("%d", &sig);
  while(1){
    printf("Enter Integer data : ");
    scanf("%d", &u.sival_int);
    sigqueue(pid, sig, u);
  }
}
