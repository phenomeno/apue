#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main (int argc, char *argv[]) {
  int val;

  if (argc != 2) {
    printf("Usage: a.out <descriptor#>\n");
    return(1);
  }

  if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0) {
    printf("Error using fcntl for fd %d\n", atoi(argv[1]));
  }

  printf("val: %d\n", val);

  switch (val & O_ACCMODE) {
  case O_RDONLY:
    printf("read only");
    break;

  case O_WRONLY:
    printf("write only");
    break;

  case O_RDWR:
    printf("read write");
    break;

  default:
    printf("Error reading file access mode.\n");
    return(1);
  }

  if (val & O_APPEND)
    printf(", append");

  if (val & O_CLOEXEC)
    printf(", close on exec");

  if (val & O_NONBLOCK)
    printf(", nonblocking mode");

  if (val & O_SYNC)
    printf(", sync writes");

  #if !defined(_POSIX_C_SOURCE) && defined(O_SYNC) && (O_FSYNC != O_SYNC)
    if (val & O_FSYNC)
      printf(", sync writes via fsync");
  #endif

  putchar('\n');

  return 0;
}
