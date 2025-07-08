#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
  int fd = open("holeFile", O_CREAT | O_RDWR, 00666);
  ftruncate(fd, 10000000);
  close(fd);
  return EXIT_SUCCESS;
}
