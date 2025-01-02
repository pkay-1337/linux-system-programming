#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  for (int i = 1; i < 4; i++) {
    switch (fork()) {
    case 0:
      printf("child process %d created \n", getpid());
      sleep(i * 10);
      exit(1);
    case -1:
      printf("Errorrrrr");
    default:
      break;
    }
  }
  /* wait(NULL); // blocks execution and wait for a child to die */
  while (1) {
    siginfo_t *s = malloc(sizeof(siginfo_t));
    int opt;
    int child =
        waitid(P_ALL, 0, s, WCONTINUED | WEXITED | WSTOPPED); //| WNOHANG);
    if (child == -1) {
      printf("no more childs ig\n");
      break;
    } else {
      printf("Child process %d ", s->si_pid);
      if (s->si_code == CLD_EXITED) {
        printf("exited ");
      }
      if (s->si_code == CLD_KILLED) {
        printf("killed ");
      }
      if (s->si_code == CLD_STOPPED) {
        printf("stopped ");
      }
      if (s->si_code == CLD_CONTINUED) {
        printf("continued ");
      }
      printf("with status : %d\n", s->si_status);
    }
  }
  return 0;
}
