#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/mman.h>

void handler(int s, siginfo_t *info, void* ucontext){
  int a = 10;
  printf("i am at %p in handler\n", &a);
  printf("clicked CTRL+c\n");
  printf("The signal is sent by : %d\n", info -> si_pid);
  printf("sender real uid : %d\n", info -> si_uid);
  printf("The signal : %d\n", info -> si_signo);
  printf("The signal code : %d\n", info -> si_code);
}

int main(){

  printf("MY PID : %d\n", getpid());
  void *mapped = mmap((void *)0x13370000, 0x10000, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
  printf("Mapped memory here : %p\n", mapped);

  stack_t *sigstack = malloc(sizeof(stack_t));
  sigstack -> ss_sp = (void *)0x13370000;
  sigstack -> ss_flags = SS_ONSTACK;
  sigstack -> ss_size = 0x10000;
  assert(sigaltstack(sigstack, NULL) == 0);

  printf("alt stack start here : %p\n", sigstack->ss_sp);


  sigset_t *set = malloc(sizeof(sigset_t));
  sigaddset(set, SIGTERM);
  struct sigaction *act = malloc(sizeof(struct sigaction));
  act -> sa_sigaction = handler;
  act -> sa_mask = *set;
  act -> sa_flags = SA_ONSTACK | SA_SIGINFO;
  for (int i = 0; i < 100; i++){
      sigaction(i, act, NULL);
  }
  int a = 10;
  printf("i am at %p in main\n", &a);
  while (1){
    printf("waiting for signal : ");
    pause();
  }
  pause();
  printf("back in main\n");
  pause();

  return 0;
} 
