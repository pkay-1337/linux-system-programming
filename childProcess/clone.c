#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#ifndef CHILD_SIG
#define CHILD_SIG                                                              \
  SIGUSR1 /* Signal to be generated on termination                             \
             of cloned child */
#endif

static int /* Startup function for cloned child */
childFunc(void *arg) {
  if (close(*((int *)arg)) == -1) {
    printf("close error");
    exit(-1);
  }

  return 0; /* Child terminates now */
}

int main(int argc, char *argv[]) {
  const int STACK_SIZE = 65536; /* Stack size for cloned child */
  char *stack;                  /* Start of stack buffer */
  char *stackTop;               /* End of stack buffer */
  int s, fd, flags;

  fd = open("/dev/null", O_RDWR); /* Child will close this fd */
  if (fd == -1) {
    printf("open error");
    exit(-1);
  }

  /* If argc > 1, child shares file descriptor table with parent */
  flags = (argc > 1) ? CLONE_FILES : 0;

  /* Allocate stack for child */

  stack = malloc(STACK_SIZE);
  if (stack == NULL) {
    printf("malloc error");
    exit(-1);
  }
  stackTop = stack + STACK_SIZE; /* Assume stack grows downward */

  /* Ignore CHILD_SIG, in case it is a signal whose default is to
     terminate the process; but don't ignore SIGCHLD (which is ignored
     by default), since that would prevent the creation of a zombie. */

  if (CHILD_SIG != 0 && CHILD_SIG != SIGCHLD)
    if (signal(CHILD_SIG, SIG_IGN) == SIG_ERR) {
      printf("signal error");
      exit(-1);
    }

  /* Create child; child commences execution in childFunc() */

  if (clone(childFunc, stackTop, flags | CHILD_SIG, (void *)&fd) == -1) {
    printf("clone error");
    exit(-1);
  }

  /* Parent falls through to here. Wait for child; __WCLONE is
     needed for child notifying with signal other than SIGCHLD. */

  if (waitpid(-1, NULL, (CHILD_SIG != SIGCHLD) ? __WCLONE : 0) == -1) {
    printf("waitpid error");
    exit(-1);
  }
  printf("child has terminated\n");

  /* Did close() of file descriptor in child affect parent? */
  s = write(fd, "x", 1);
  if (s == -1 && errno == EBADF)
    printf("file descriptor %d has been closed\n", fd);
  else if (s == -1)
    printf("write() on file descriptor %d failed ", fd);
  else
    printf("write() on file descriptor %d succeeded\n", fd);

  exit(EXIT_SUCCESS);
}
