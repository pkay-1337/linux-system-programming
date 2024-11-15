#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int counter = 0;

void interrupthandler(int s){
  counter++;
  printf("Clicked ctrl+c %d\n", counter);
}

int main(){
  void (*oldhandler)(int);
  oldhandler = signal(2, interrupthandler);
  while (1){
    char buf;
    read(0, &buf, 1);
  }
  return 0;
}
