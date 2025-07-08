#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
  unsigned long long hole_size;
  printf("size of file hole : ");
  scanf("%d", &hole_size);
  int fd = open("file_with_hole", O_CREAT | O_RDWR, 00666);
  write(fd, "Test", 4);
  lseek(fd, hole_size, SEEK_END);
  write(fd, "Test", 4);
  close(fd);
  return EXIT_SUCCESS;
}
