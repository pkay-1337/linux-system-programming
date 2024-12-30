#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void cleaner() {
  printf("Bye, World!\n");
  /* exit(69); */
}
void cleaner2(int a, void *s) { printf("%d %s\n", a, (char *)s); }

int main(int argc, char *argv[]) {
  atexit(cleaner);
  on_exit(cleaner2, "Message");
  printf("Hello, World!\n");
  /* _exit(99); */
  exit(69);
  return EXIT_SUCCESS;
}
