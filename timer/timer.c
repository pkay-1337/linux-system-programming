#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
  struct itimerval *new, *old;
  struct timeval timer, interval;
  int a;
  new = malloc(sizeof(struct itimerval));
  old = malloc(sizeof(struct itimerval));
  interval.tv_sec = 0;
  interval.tv_usec = 0;
  timer.tv_sec = 5;
  new->it_interval = interval;
  new->it_value = timer;

  setitimer(ITIMER_REAL, new, old);
  scanf("%d", &a);
  return EXIT_SUCCESS;
}
