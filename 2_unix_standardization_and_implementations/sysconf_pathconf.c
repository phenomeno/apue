#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define MAXSIZE 4096

void append_char_to_string(char *s, char c);
void split_from_whitespace(char *input, char *token1, char *token2);

int main(void) {
  FILE *f;
  char *buf;
  char *name;
  char *mesg;
  long val;

  f = fopen("pathconf.sym", "r");
  if (f == NULL) {
    printf("file open error");
    exit(0);
  }

  buf = (char *) malloc(MAXSIZE);
  name = (char *) malloc(MAXSIZE);
  mesg = (char *) malloc(MAXSIZE);

  while (fgets(buf, MAXSIZE, f)) {
    split_from_whitespace(buf, mesg, name);
    printf("%s=", mesg);
    printf("%s\n", name);
    mesg[0] = '\0';
    name[0] = '\0';
  }

  free(buf);

  /* mfw i realize the config names are constants */
  errno = 0;
  val = pathconf("pathconf.sym", _PC_LINK_MAX); /* valid config name */
  // val = pathconf("pathconf.sym", _PC_SYMLINK_MAX); /* indeterminate */
  // val = pathconf("pathconf.sym", 100000); /* error */
  if (val == -1) {
    if (errno == 0) {
      printf("_PC_LINK_MAX: Limit is indeterminate.\n");
    } else {
      perror("_PC_LINK_MAX");
    }
  } else {
    printf("_PC_LINK_MAX: %ld\n", val);
  }

  return 0;
}

void append_char_to_string(char *s, char c) {
  int x;

  x = strlen(s);
  s[x] = c;
  s[x + 1] = '\0';
}

void split_from_whitespace(char *input, char *token1, char *token2) {
  int n, first_whitespace = 0;

  for (n = 0; n < strlen(input) - 1; n++) {
    if (input[n] == '\t') {
      if (first_whitespace == 0) {
        first_whitespace = 1;
        continue;
      } else {
        continue;
      }
    }

    if (first_whitespace == 0) {
      append_char_to_string(token1, input[n]);
   } else {
     append_char_to_string(token2, input[n]);
   }
  }
}
