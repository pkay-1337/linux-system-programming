#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  for (int i = 1; i < 3; i++) {
    /* printf("%s\n", argv[i]); */
    switch (fork()) {
    case 0:
      printf("child process %d created \n", getpid());
      sleep(20);
      exit(99);
    case -1:
      printf("Errorrrrr");
    default:
      break;
    }
  }
  /* wait(NULL); // blocks execution and wait for a child to die */
  while (1) {
    int *s = malloc(4);
    int opt;
    int child = waitpid(-1, s, WUNTRACED | WCONTINUED); //| WNOHANG);
    if (child == 0) {
      printf("no change in child status\n");
    } else if (child == -1) {
      printf("no more childs ig\n");
      break;
    } else {
      printf("Child process %d chanced state STATUS:%x\n", child, *s);
    }
  }
  return 0;
}
