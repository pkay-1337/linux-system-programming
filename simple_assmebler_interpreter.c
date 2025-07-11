#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int n = 6;
void get_part(int index, char des[], const char* source){
  if(index == 0) sscanf(source, "%s %*s %*s", des);
  if(index == 1) sscanf(source, "%*s %s %*s", des);
  if(index == 2) sscanf(source, "%*s %*s %s", des);
}
int check_operation(const char* instruction){
  char operation[4] = {0};
  get_part(0, operation, instruction);
  if(strcmp(operation, "mov") == 0) return 0;
  if(strcmp(operation, "inc") == 0) return 1;
  if(strcmp(operation, "dec") == 0) return 2;
  if(strcmp(operation, "jnz") == 0) return 3;

  // printf("operation = %s\n", operation);

}

int is_const(char *x){
  if(x[0] >= 0x61 && x[0] <= 0x7a){
    return 0;
  }else return 1;
}
void run_instruction(int *x, const char *const program[n], int registers[]){
  char *o1 = (char*)malloc(256);
  char *o2 = (char*)malloc(256);
  int c;

  
  const char *instruction = program[(*x)-1];
  int op = check_operation(instruction);
  switch (op){
    case 0:
      get_part(1, o1, instruction);
      get_part(2, o2, instruction);
      if(is_const(o2)){
        sscanf(o2, "%d", &c);
        registers[o1[0]] = c;
      }else{
        registers[o1[0]] = registers[o2[0]];
      }
      (*x)++;
      break;
    case 1:
      // inc(instruction);
      get_part(1, o1, instruction);
      registers[o1[0]] = registers[o1[0]] + 1;
      (*x)++;
      break;
    case 2:
      // dec(instruction);
      get_part(1, o1, instruction);
      registers[o1[0]] = registers[o1[0]] - 1;
      (*x)++;
      break;
    case 3:
      // jnz(instruction);

      (*x)++;
      break;
      
  }
  // (*x)++;
  
}
void simple_assembler (size_t n, const char *const program[n], int registers[])
{
// fill the registers[] table
// register a goes in registers['a'], b in registers['b'], and so on
// you need not worry about unused registers
    // TODO
    // create a program counter
    // create a run instruction function
      // create a check operation function
        // create a check register or constant function
  int pc = 1;
  while(pc <= n){
    run_instruction(&pc, program, registers);
  }
  printf("a = %d\n", registers['a']);
}

int main(int argc, char *argv[])
{
  int reg[128];
  const char *const program[] = {"mov a 5","inc a","dec a","dec a","jnz a -1", "dec a"};
  simple_assembler(n, program, reg);

  return EXIT_SUCCESS;
}
