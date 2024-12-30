#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("give child TTL\n");
  }
  for (int i = 1; i < argc; i++) {
    /* printf("%s\n", argv[i]); */
    switch (fork()) {
    case 0:
      printf("child process %d created will sleep for %d seconds\n", getpid(),
             atoi(argv[i]));
      sleep(atoi(argv[i]));
      exit(i);
    case -1:
      printf("Errorrrrr");
    default:
      break;
    }
  }
  /* wait(NULL); */
  while (1) {
    int child = wait(NULL);
    if (child == -1) {
      printf("No more childs\n");
      break;
    } else {
      printf("Child process %d died.\n", child);
    }
  }
  return 0;
}
