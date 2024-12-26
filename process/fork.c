#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
static int idata = 111; /* Allocated in data segment */

int main(int argc, char *argv[]) {
  int *a = malloc(4);
  int istack = 222; /* Allocated in stack segment */
  int childPid;

  switch (childPid = fork()) {
  case -1:
    printf("Error");

  case 0:
    printf("child %p\n", a);
    *a = 5;
    idata *= 3;
    istack *= 3;
    break;

  default:
    printf("parent %p\n", a);
    *a = 10;
    sleep(1);
    break;
  }

  /* Both parent and child come here */

  printf("PID=%ld %s idata=%d istack=%d a=%d\n", (long)getpid(),
         (childPid == 0) ? "(child) " : "(parent)", idata, istack, *a);

  exit(0);
}
