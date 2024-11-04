#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  struct timeval * t;
  printf("address = %p\n", t);
  /* t = malloc(sizeof(struct timeval)); */
  t = sbrk(0x10);
  gettimeofday(t,0);
  printf("size : %d\n", sizeof(t->tv_sec));
  printf("%ld\n", t->tv_sec);



  time_t *tt;
  *tt = time(0);

  printf("time = %d\n", *tt);
  printf("time = %s\n", ctime(tt));

}
