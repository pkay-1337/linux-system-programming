#include <unistd.h>
int main(int argc, char *argv[], char *envp[]) {
  char *a[] = {"/bin/firefox", NULL};
  execve("/bin/firefox", a, envp);
  return 0;
}
