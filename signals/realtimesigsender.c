#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  int pid, sig;
  union sigval u;
  printf("MY PID : %d\n", getpid());
  printf("Enter PID : ");
  scanf("%d", &pid);
  while (1) {
    printf("Enter SIGNAL NUMBER : ");
    scanf("%d", &sig);
    printf("Enter Integer data : ");
    scanf("%d", &u.sival_int);
    sigqueue(pid, sig, u);
  }
  return 0;
}
