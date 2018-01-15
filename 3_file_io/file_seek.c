#include <errno.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
  errno = 0;

  if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1) {
    if (errno == ESPIPE) {
      printf("Not able to seek standard input.");
    } else {
      printf("Some other error.");
    }
  } else {
    printf("Seek ok.");
  }
}
