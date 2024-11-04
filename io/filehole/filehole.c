#include <unistd.h>
#include <fcntl.h>
int main(){
  int fd = open("test", O_RDWR);
  lseek(fd, 10000, SEEK_END);
  char * buff = "AAAAAAAAAAAAAA";
  write(fd, buff, sizeof(buff));
  close(fd);
  return 0;
}
