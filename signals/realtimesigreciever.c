#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int s, siginfo_t *i, void *x){
  printf("signal : %d\n", s);
  printf("sender : %d\n", i -> si_pid);
  printf("value : %d\n", i -> si_value.sival_int);
}
int main(){
  printf("MY PID : %d\n", getpid());
  printf("%d - %d\n", SIGRTMIN, SIGRTMAX);
  struct sigaction *act = malloc(sizeof(struct sigaction));
  act -> sa_sigaction = handler;
  act -> sa_flags = SA_SIGINFO;
  sigaction(34, act, NULL);
  while (1){
    pause();
    printf("------------\n");
  }
  return 0;
}
