#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif

#define OPEN_MAX_GUESS 256

long open_max(void);

int main(void) {
  printf("OPEN_MAX: maximum number of files that a process can have open at a time\n%ld\n", open_max());
  return 0;
}

long open_max(void) {
  if (openmax == 0) {
    errno = 0;
    if ((openmax = sysconf(_SC_OPEN_MAX)) < 0) {
      if (errno == 0) {
        openmax = OPEN_MAX_GUESS; /* _SC_OPEN_MAX is an indeterminate value */
      } else {
        printf("sysconf error checking _SC_OPEN_MAX\n");
        exit(1);
      }
    }
  }

  return openmax;
}
