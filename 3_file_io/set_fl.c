#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

void set_fl(int fd, int flags) {
  int val;

  if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
    printf("Error using fcntl F_GETFL on fd %d\n", fd);
    return 1;
  }

  val |= flags;

  if ((fcntl(fd, F_SETFL, val)) < 0) {
    printf("Error using fcntl F_SETFL on fd %d\n", fd);
    return 1;
  }
};
