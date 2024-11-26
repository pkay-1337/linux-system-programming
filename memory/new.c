#include <stdio.h>
#include <stdlib.h>

int main() {
  int *b;
  b = malloc(4);
  *b = 300;
  printf("%d\n", *b);
}
