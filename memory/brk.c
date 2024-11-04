#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
  void *b = sbrk(0);
  printf("address of break = %p\n", b);
  b = sbrk(0x10);
  printf("address of break = %p\n", b);
  b = sbrk(0x10);
  printf("address of break = %p\n", b);
  b = b+0x100;
  brk(b);
  b = sbrk(-0x10);
  printf("address of break = %p\n", b);
  b = sbrk(0x0);
  printf("address of break = %p\n", b);
  return 0;
}
