#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void) {
  int fd;
  mode_t mode = S_IRUSR | S_IWUSR;

  if ((fd = creat("file.hole", mode)) < 0) {
    printf("creat error");
  }

  // offset at 10
  if (write(fd, buf1, 10) != 10) {
    printf("buf1 write error");
  }

  // offset at 10 + 100
  if (lseek(fd, 100, SEEK_END) == -1) {
    printf("lseek error");
  }

  // offset at 10 + 100 + 10
  if (write(fd, buf2, 10) != 10) {
    printf("buf2 write error");
  }

  return 0;
}
