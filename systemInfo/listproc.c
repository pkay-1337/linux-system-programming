#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

char user[255];
char path[4096];
int fd;
char statusline[1024];
char *pstr = "Pid:\t";
char *nstr = "Name:\t";
char pid[10];
char name[256];
char temp[1] = {1};
int l = 1;
char uuid[20];
char uid[20];
int main(int argc, char *argv[]){
  char *optstring = ":u:";
  int opt = getopt(argc, argv, optstring);
  if((unsigned char) opt == 'u'){
    sprintf(user, "%s", optarg);
    printf("user : %s\n", user);
    
    struct passwd *pwd;
    pwd = getpwnam(user);
    if(pwd != NULL) {
      printf("UID : %d\n", pwd -> pw_uid);
      sprintf(uuid, "%d", pwd -> pw_uid);
      // printf("UID str : %s\n", uid);
    }

    DIR *dir;
    dir = opendir("/proc/");
    if(dir == NULL){
      printf("Unable to open proc directory.\n");
    }

    struct dirent *d;
    while( d = readdir(dir)){
      if( d -> d_name[0] >= 0x30 && d -> d_name[0] <= 0x39 ){
        sprintf(path, "/proc/%s/status", d -> d_name);
        fd = open(path, O_RDONLY);
        if (fd != -1){
          l = 1;
          while (l != 0){
            for(int i = 0;;i++){
              l = read(fd, temp, 1);
              if(temp[0] == EOF || temp[0] == '\n') break;
              statusline[i] = temp[0];
            }
            if(strncmp("Uid:\t", statusline, 5) == 0){
              sscanf(statusline, "Uid:\t%s\t", uid);
            }
            if(strncmp(pstr, statusline, 5) == 0){
              sscanf(statusline, "Pid:\t%s\t", pid);
            }
            if(strncmp(nstr, statusline, 6) == 0){
              sscanf(statusline, "Name:\t%s\n", name);
            }
            memset(statusline, 0, 1024);
          }

          if(strcmp(uid, uuid) == 0)
          printf("%s\t---\t%s\n", pid, name);
          // printf("Owner uid : %s\n", uid);
          memset(pid, 0, 10);
          memset(name, 0, 256);
        }
        close(fd);
      }
    }


    






  }else if((unsigned char) opt == ':'){
    printf("Argument missing : -%c <user>\n", (unsigned char)optopt);
  }else{
    printf("Argument missing : -u <user>\n");
  }
  return EXIT_SUCCESS;
}
