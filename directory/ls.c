#include <stdio.h>
#include <dirent.h>
#include <assert.h>
#include <unistd.h>

int main(int argc, char **argv){
  DIR *d;
  struct dirent *dirs;

  if(argc > 1){
    d = opendir(argv[1]);
    assert(d != NULL);
  }else{
    char buf[128];
    int len = read(0, buf, 128);
    buf[len-1] = 0;
    d = opendir(buf);
  }

cmdl:
  while (1){
    dirs = readdir(d);
    if(dirs == NULL) break;
    printf("%s\n",dirs->d_name);
  } 

  return 0;
}
