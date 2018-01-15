#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

long get_open_max(void);
int dup_2(int fd, int fd2);

// guide: https://github.com/clamiax/training/blob/master/exercises/apue/ex-3.2.c

int main(void) {
  int fd;
  char s[] = "testing\n";

  if ((fd = dup_2(1, 5)) == -1) {
    printf("Error running dup_2\n");
    return 1;
  }

  printf("File descriptor: %d\n", fd);
  write(fd, s, strlen(s));

  return 0;
}

long get_open_max(void) {
  long open_max;

  if ((open_max = sysconf(_SC_OPEN_MAX)) == -1) {
    perror("Error using sysconf to find OPEN_MAX value.");
  };

  return open_max;
}

int dup_2(int fd, int fd2) {
  long open_max;
  int fd_counter = 0, *fds_list;

  open_max = get_open_max();

  if (fd >= open_max || fd2 >= open_max || fd < 0 || fd2 < 0) {
    return -1;
  }

  if (fd == fd2) {
    return fd2;
  }

  close(fd2);

  if ((fds_list = calloc(open_max, sizeof(int))) == NULL) {
    printf("Error during calloc\n");
    return 1;
  }

  while ((fds_list[fd_counter] = dup(fd)) != fd2) {
    fd_counter++;
  }

  while (--fd_counter >= 0) {
    close(fds_list[fd_counter]);
  }

  free(fds_list);

  return fd2;
}
