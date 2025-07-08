#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
  char *source = argv[1];
  char *dest = argv[2];
  printf("source : %s\n", source);
  printf("destination : %s\n", dest);
  int fds = open(source, O_RDONLY);
  int fdd = open(dest, O_WRONLY | O_CREAT, 00666);
  int size = lseek(fds, 0, SEEK_END);
  lseek(fds, 0, SEEK_SET);
  char buf[1];
  buf[0] = 'a';
  for(int i=0; i < size; i++){
    read(fds, buf, 1);
    write(fdd,buf, 1);
  }
  close(fds);
  close(fdd);

  return EXIT_SUCCESS;
}

