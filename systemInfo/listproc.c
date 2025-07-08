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
char temp[1] = {1};
int l = 1;
char uuid[20];

char * getArg(int argc, char *argv[]){
  char *optstring = ":u:";
  int opt = getopt(argc, argv, optstring);
  if((unsigned char) opt == 'u'){
    return optarg;
  }else if((unsigned char) opt == ':'){
    printf("Argument missing : -%c <user>\n", (unsigned char)optopt);
    exit(1);
  }else{
    printf("Argument missing : -u <user>\n");
    exit(1);
  }
}

int getUUID(char* user){
  struct passwd *pwd;
  pwd = getpwnam(user);
  if(pwd != NULL) {
    return pwd -> pw_uid;
  }
}

struct details {
  char pid[20];
  char name[256];
  char uid[20];
};

struct details* getDetails(char * path){
  struct details *d;
  d = (struct details *) malloc(sizeof(struct details));
  char statusline[1024] = {0};
  int fd = open(path, O_RDONLY);
  if (fd != -1){
    l = 1;
    while (l != 0){
      for(int i = 0;;i++){
        l = read(fd, temp, 1);
        if(temp[0] == EOF || temp[0] == '\n') break;
        statusline[i] = temp[0];
      }
      if(strncmp("Uid:\t", statusline, 5) == 0){
        sscanf(statusline, "Uid:\t%s\t", d->uid);
      }
      if(strncmp("Pid:\t", statusline, 5) == 0){
        sscanf(statusline, "Pid:\t%s\t", d->pid);
      }
      if(strncmp("Name:\t", statusline, 6) == 0){
        sscanf(statusline, "Name:\t%s\n", d->name);
      }
      memset(statusline, 0, 1024);
    }
    close(fd);
  }
  return d;
}


int main(int argc, char *argv[]){
    char *user = getArg(argc, argv);
    printf("user : %s\n", user);
    sprintf(uuid, "%d", getUUID(user));

    DIR *dir;
    dir = opendir("/proc/");
    if(dir == NULL){
      printf("Unable to open proc directory.\n");
    }

    struct dirent *d;
    while( d = readdir(dir)){
      if( d -> d_name[0] >= 0x30 && d -> d_name[0] <= 0x39 ){
        sprintf(path, "/proc/%s/status", d -> d_name);
        struct details *d;
        d = getDetails(path);
        if(strcmp(d->uid, uuid) == 0)
        printf("%s\t---\t%s\n", d->pid, d->name);
        free(d);
      }
    }
  return EXIT_SUCCESS;
}
