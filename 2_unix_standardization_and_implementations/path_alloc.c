#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#ifdef PATH_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif

static long posix_version = 0;
static long xsi_version = 0;

#define PATH_MAX_GUESS 4096
#define MAXSIZE 4096

char * path_alloc(size_t * sizep);

int main(void) {
  char *buf, *cwd;
  size_t size;

  buf = path_alloc(&size);
  cwd = getcwd(buf, size);

  if (cwd == NULL) {
    strerror(errno);
  } else {
    printf("current working directory is: %s\n", cwd);
  }
  return 0;
}

char * path_alloc(size_t * sizep) {
  char *ptr;
  size_t size;

  if (posix_version == 0)
    posix_version = sysconf(_SC_VERSION);

  if (xsi_version == 0)
    xsi_version = sysconf(_SC_XOPEN_VERSION);

  if (pathmax == 0) {
    errno = 0;
    if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
      if (errno == 0) {
        pathmax = PATH_MAX_GUESS; /* _PC_PATH_MAX is an indeterminate value */
      } else {
        printf("pathconf error for _PC_PATH_MAX\n");
        exit(1);
      }
    }
  }

  if ((posix_version < 200112L) && (xsi_version < 4))
    size = pathmax + 1; /* prior to POSIX.1-2001 and XPG3 not guaranteed to count terminating null byte */
  else
    size = pathmax;

  if ((ptr = malloc(size)) == NULL) {
    printf("malloc error for pathname");
    exit(1);
  }

  if (sizep != NULL)
    *sizep = size;

  return ptr;
}
