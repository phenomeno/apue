#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
  mode_t mode = S_IRUSR | S_IWUSR;
  int fd, val;
  char *file_read;
  char contents[] = "123456789";
  char test[] = "hi";

  file_read = malloc(20);

  fd = open("lseek_test.txt", O_RDWR | O_APPEND | O_CREAT, mode);
  write(fd, contents, 10);
  lseek(fd, 0, SEEK_SET);
  read(fd, file_read, 10);
  printf("%s\n", file_read);
  lseek(fd, 0, SEEK_SET);
  if ((val = write(fd, test, 2)) == -1) {
    printf("Write error.\n");
    return 1;
  }

  return 0;
}
