#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
  struct utsname details;
  printf("%p\n", &details);
  int x = uname(&details);
  printf("Node name: %s\n", details.nodename);
  printf("System name: %s\n", details.sysname);
  printf("Release: %s\n", details.release);
  printf("Version: %s\n", details.version);
  printf("Machine: %s\n", details.machine);
  return 0;
}
