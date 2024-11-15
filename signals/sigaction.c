#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int s){
  printf("clicked CTRL+c\n");
}

int main(){
  sigset_t *set = malloc(sizeof(sigset_t));
  sigaddset(set, SIGTERM);
  struct sigaction *act = malloc(sizeof(struct sigaction));
  act -> sa_handler = handler;
  act -> sa_mask = *set;
  sigaction(2, act, NULL);
  pause(); 
  printf("back in main\n");
  pause();

  return 0;
}
