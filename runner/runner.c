#include <sys/inotify.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BUF_LEN 1024

int main(int argc, char **argv){

  char buf[BUF_LEN];
  for(;;){
    int fd = inotify_init();
    int wd = inotify_add_watch(fd, argv[1], IN_MODIFY);
    assert(wd != -1);

    int r = read(fd, buf, BUF_LEN);
    int x = buf[0];

    if(x == wd){
      int fork_val = fork();
      if (fork_val == 0){
        system("rm a.out");
        char gcc[40] = "gcc ";
        strcat(gcc, argv[1]);
        system(gcc);
        system("./a.out");
        system("echo -e '\n---------------------------------------'");
        exit(5);
      }
    }
    inotify_rm_watch(fd, wd);

    close(fd);
  }

}
