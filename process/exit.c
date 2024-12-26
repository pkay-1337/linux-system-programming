#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void cleaner() {
  printf("Bye, World!\n");
  /* exit(69); */
}

int main(int argc, char *argv[]) {
  atexit(cleaner);
  printf("Hello, World!\n");
  /* _exit(99); */
  return EXIT_SUCCESS;
}
