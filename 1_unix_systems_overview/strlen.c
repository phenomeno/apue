#include <stdlib.h>
#include <stdio.h>

int strlen2(char *s);

int main(void) {
  printf("%d\n", strlen2("hi grace"));
  exit(0);
}

int strlen2(char *s) {
  int n;

  for (n = 0; *s != '\0'; s++)
    n++;

  return n;
}
