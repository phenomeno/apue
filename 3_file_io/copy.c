#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFSIZE 4096

int main(void) {
  int n;
  char *buf;

  buf = malloc(BUFFSIZE);

  while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
     if (write(STDOUT_FILENO, buf, n) != n) {
       printf("error writing");
       return 1;
     }

  if (n < 0) {
    printf("read error");
    return 1;
  }

  return 0;
}
