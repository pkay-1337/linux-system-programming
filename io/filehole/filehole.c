#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(){
  int fd = open("file", O_RDWR | O_CREAT);
  lseek(fd, 536870912000, SEEK_END);
  char * buff = "AAAAAAAAAAAAAA";
  write(fd, buff, sizeof(buff));
  close(fd);
  return 0;
}
