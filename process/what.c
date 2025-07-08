#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("Hello, World!\n");
  write(1, "ciao\n", 5);
  fork();
  // _exit(69); 
  exit(69);
}
/* Cooooooooooooooooooool */
