#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char path[256];
  char rpath[256];
  memset(path, 0, 256);
  int len = read(1, path, 255);
  readlink(path, rpath, 255);
  printf("%s\n", rpath);
  return EXIT_SUCCESS;
}
