#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/sysmacros.h>

int main(){
  char *pathname = "./stat.c";
  struct stat statbuf;
  stat(pathname, &statbuf);
  printf("%d\n", statbuf.st_dev);
  printf("major dev id : %d\nminor dev id : %d\n", major(statbuf.st_dev), minor(statbuf.st_dev));
  printf("i-node number : %ld\n", statbuf.st_ino);
  printf("uid number : %ld\n", statbuf.st_uid);
  return 0;
}
