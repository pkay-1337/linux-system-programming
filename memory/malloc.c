#include <stdio.h>
struct test{
  int num;
  char a;
};
int main(int argc, char *argv[]){
  struct test a;
  a.num = 0xffffffff;
  a.a = 0xff;
  printf("num = %d\na = %d\n", a.num, a.a);
  struct test *Test;
  printf("value of test = %p\n", Test);
  printf("size of test = %d\n", sizeof(Test));
  Test = (struct test*)malloc(sizeof(struct test));
  printf("value of test = %p\n", Test);
  printf("size of test = %d\n", sizeof(Test));
  Test -> num = 5;
  return EXIT_SUCCESS;
}

