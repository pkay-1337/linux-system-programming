#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int optind, opterr, optopt;
char *optarg;
char file[255];
int main(int argc, char *argv[]){
  char *optstring = ":i:";
  int opt = getopt(argc, argv, optstring);
  if((unsigned char) opt == 'i'){
    sprintf(file, "%s", optarg);
    printf("file : %s\n", file);
    int fd = open(file, O_RDWR | O_CREAT | O_APPEND | O_SYNC, 00666);
    char buf[1];
    buf[0] = 'a';
    while (buf[0] != EOF){
      read(0, buf, 1);
      printf("%c", buf[0]);
      write(fd, buf , 1);

    }
  }else if((unsigned char) opt == ':'){
    printf("Argument missing : -%c [file]\n", (unsigned char)optopt);
  }else{
    char buf[1];
    buf[0] = 'a';
    while (buf[0] != EOF){
      read(0, buf, 1);
      printf("%c", buf[0]);
    }
  }
  return 0;
}
