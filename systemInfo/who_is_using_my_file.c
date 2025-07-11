#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#define SIZE PATH_MAX

char *path;
char *fdpath;
char rpath[SIZE];
char lpath[SIZE];

char* getpath(int argc, char *argv[]){
  char *optstring = ":p:";
  int opt = getopt(argc, argv, optstring);
  if((unsigned char) opt == 'p'){
    return optarg;
  }else if((unsigned char) opt == ':'){
    printf("Argument missing : -%c <path>>\n", (unsigned char)optopt);
    exit(1);
  }else{
    printf("Argument missing : -p <path>\n");
    exit(1);
  }
}
DIR* getdirstream(char* p){
  DIR *dir;
  dir = opendir(p);
  return dir;

}

char * getprocessname(char* pid){
  char* commandfile;
  commandfile = malloc(256);
  sprintf(commandfile, "/proc/%s/comm", pid);
  char *command;
  command = malloc(256);
  read(open(commandfile, O_RDONLY), command, 256);
  return command;
}
int main(int argc, char *argv[])
{
  path = malloc(SIZE);
  fdpath = malloc(SIZE);
  path = getpath(argc, argv);
  realpath(path, rpath);
  printf("File Path : %s\n", path);
  printf("Realpath : %s\n", rpath);

  DIR *proc = getdirstream("/proc");

  struct dirent *d;
  while(d = readdir(proc)){
    if( d -> d_name[0] >= 0x30 && d -> d_name[0] <= 0x39 ){
      // if it is a process dir containing numbers
      sprintf(fdpath, "/proc/%s/fd", d -> d_name);
      // printf("FD path = %s\n", fdpath);
      DIR *fd = getdirstream(fdpath);
      struct dirent *dd;
      while(dd = readdir(fd)){
        sprintf(fdpath, "/proc/%s/fd/%s", d -> d_name, dd -> d_name);
        readlink(fdpath, lpath, SIZE-1);
        // printf("\tFull fd path : %s\n\t\tLink path : %s\n", fdpath, lpath);
        if(strcmp(lpath, rpath) == 0){
          printf("This file is opened by process %s pid %s\n", getprocessname(d -> d_name), d -> d_name);
        }
        memset(lpath, 0, SIZE);
      }

    }
  }
  // readlink(path, rpath, SIZE-1);
  // printf("%s\n", rpath);
  return EXIT_SUCCESS;
}
