#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
  printf("Working\n");
  long m = sysconf(_SC_OPEN_MAX);
  printf("Max fd : %ld\n", m);
  printf("Page size : %ld\n", sysconf(_SC_PAGESIZE));
  printf("File name : %ld\n", pathconf("./",_PC_NAME_MAX));
  //read(0, &m, 1);
  return EXIT_SUCCESS;
}



