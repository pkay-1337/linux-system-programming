#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>

int *proc_ids;
char path[4096];
char temp[1] = {1};

typedef struct process process;
struct process{
  int pid;
  int ppid;
  char name[256];
  int clen;
  process *childs[100];
  int printed;
};

int get_number_of_processes(){
  int num;
  int fd = open("/proc/loadavg", O_RDONLY);
  char data[256];
  read(fd, data, 256);
  sscanf(data, "%*f %*f %*f %*d/%d", &num);
  return num;
}

void getProcs(){
  DIR *dir;
  dir = opendir("/proc/");
  if(dir == NULL){
    printf("Unable to open proc directory.\n");
  }

  struct dirent *d;
  int i = 0;
  while( d = readdir(dir)){
    if( d -> d_name[0] >= 0x30 && d -> d_name[0] <= 0x39 ){ 
      int temp;
      sscanf(d -> d_name, "%d", &temp);
      proc_ids[i++] = temp;

    }
  }
}


process* getdetails(char * path){
  process *p;
  p = (process*) malloc(sizeof(process));
  char statusline[1024] = {0};
  int fd = open(path, O_RDONLY);
  int pid; int ppid;
  int l = 1;
  if (fd != -1){
    l = 1;
    while (l != 0){
      for(int i = 0;;i++){
        l = read(fd, temp, 1);
        if(temp[0] == EOF || temp[0] == '\n') break;
        statusline[i] = temp[0];
      }
      if(strncmp("Pid:\t", statusline, 5) == 0){
        sscanf(statusline, "Pid:\t%d\t", &(p->pid));
      }
      if(strncmp("Name:\t", statusline, 6) == 0){
        sscanf(statusline, "Name:\t%s\n", p -> name);
      }
      if(strncmp("PPid:\t", statusline, 6) == 0){
        sscanf(statusline, "PPid:\t%d\n", &(p->ppid));
      }
      memset(statusline, 0, 1024);
    }
    close(fd);
    
  
    return p;
  }
}

void add_child(process *l[], process *p){
  int i = 0;
  int ppid = p -> ppid;
  int pid = p -> pid;
  process *x;
  while((x = l[i++]) != NULL){
    if (ppid == 0) break;
    if (x -> pid == ppid){
      x -> childs[x->clen] = p;
      x -> clen++;
      break;
    }
  }
}

int level = 0;
int print_process(process* p){
  if(p == NULL){
    return 0;
  }
  for(int i = 0; i < level; i++){
    printf("|   ");
  }
  printf("|---");
  printf("%s - %d - %d\n", p -> name, p -> pid, p -> ppid);
  p -> printed = 1;
  for( int i = 0; i < p -> clen; i++){
    level++;
    print_process((p -> childs)[i]);
  }
  level--;
}

void print_tree(process *l[], int len){
  for(int i = 0; i < len; i++){
    if(l[i] -> printed != 1){
    level = 0;
    print_process(l[i]);
    }
  }
}


int main(int argc, char *argv[]){
  int num = get_number_of_processes();
  process *proc_list[num];
  memset(proc_list, 0, sizeof(proc_list));
  printf("Number of processes : %d\n", num);
  proc_ids = (int*)malloc(num * sizeof(int));
  getProcs();
  int i = 0;
  int pid;

  while((pid = proc_ids[i]) > 0 ){
    // printf("%d\n", pid);
    sprintf(path, "/proc/%d/status", pid);
    process *p = getdetails(path);
    // printf("Pid : %d\t PPid : %d\t command : %s\n", p->pid, p->ppid, p->name);
    proc_list[i] = p;
    // printf("p : %p\t proc_list[i] : %p\n", p, proc_list[i]);
    add_child(proc_list, p);
    i++;
  }
  printf("count : %d\n", i);
  print_tree(proc_list, i);
  return EXIT_SUCCESS;
}
