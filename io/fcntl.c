#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/sendfile.h>
#include <unistd.h>

int main() {
  int fd = open("./test", O_WRONLY | O_CREAT, 0644);
  printf("Flags before for writing : %o\n", O_CREAT | O_WRONLY);
  assert(write(fd, "hi\n", 3) == 3);
  int flags = fcntl(fd, F_GETFL);
  printf("FNCTL flags : %o\n", flags);
  printf("is it writable? %o\n", flags & O_WRONLY);
  printf("is it readable? %o\n", flags & O_RDONLY);

  printf("Trying to change file fd flags using FCNTL F_SETFL\n");

  flags = O_RDWR;
  printf("checking flags to set : %o\n", flags);

  assert(fcntl(fd, F_SETFL, flags) != -1);

  printf("is it readable & writable? %o\n", flags & O_RDWR);
  char buf[10];
  printf("read? %ld\n", read(fd, buf, 3));
  printf("%s", buf);
  printf("FCNTL doesn't affect read/write flags, meh...\n");

  printf("\nDuplicating fd now\n");

  printf("duping %d to fd 10: %d\n", fd, dup2(fd, 10));
  // printf("duping %d to fd 10 using dup3 with custom flags: %d", fd, dup3(fd,
  // 10, O_RDWR));
  printf("dup3 not working idk why...");
}
