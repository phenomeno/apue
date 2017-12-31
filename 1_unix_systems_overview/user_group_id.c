#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  printf("User id of calling process: %d, group id of calling process: %d\n", getuid(), getgid());
  exit(0);
}
