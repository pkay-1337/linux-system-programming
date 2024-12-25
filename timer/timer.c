#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
int secs = 0;
void alarmHandler(int x) {
  secs++;
  printf("seconds : %d\n", secs);
  /* printf("%d\n", x); */
}
int main(int argc, char *argv[]) {

  void (*oldHandler)(int) = signal(14, alarmHandler);

  struct itimerval *new, *old;
  struct timeval timer, interval;
  int a;
  new = malloc(sizeof(struct itimerval));
  old = malloc(sizeof(struct itimerval));
  interval.tv_sec = 1;
  interval.tv_usec = 0;
  timer.tv_sec = 1;
  new->it_interval = interval;
  new->it_value = timer;

  setitimer(ITIMER_REAL, new, old);
  scanf("%d", &a);
  return EXIT_SUCCESS;
}
