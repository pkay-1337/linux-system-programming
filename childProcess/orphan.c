#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  for (int i = 1; i < 4; i++) {
    /* printf("%s\n", argv[i]); */
    switch (fork()) {
    case 0:
      printf("child process %d created\n", getpid());
      sleep(i * 5);
      printf("my id : %d, parent id : %d\n", getpid(), getppid());
      exit(i);
    case -1:
      printf("Errorrrrr");
    default:
      break;
    }
  }
  sleep(6);
  printf("i'm parent my id : %d\n", getpid());
  return 0;
}
