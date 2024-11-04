#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void read_args(int x, char *buf){
  while(x > 0){
    int z = printf("%s\n", buf);
    x--;
    buf = buf+z;
  }
}

int main(int argc)
{
  char buff[128];
  int fd = open("/proc/self/cmdline", O_RDONLY);
  read(fd, buff, 128);
  read_args(argc, buff);
  return 0;
}

