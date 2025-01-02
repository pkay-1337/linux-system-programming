#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  for (int i = 1; i < 2; i++) {
    switch (fork()) {
    case 0:
      printf("child process %d created\n", getpid());
      printf("killing child");
      exit(i);
    case -1:
      printf("Errorrrrr");
    default:
      break;
    }
  }
  printf("i'm parent my id : %d\n", getpid());
  printf("not waiting for child to die, it should become a zombie now\n");
  sleep(30);
  return 0;
}
