#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> /* in order to use execlp */
#include <sys/wait.h> /* waitpid */
#include <string.h> /* strlen */
#include <signal.h>

#define MAXLINE 255

static void sig_int(int);

int main(void) {
  char buf[MAXLINE];
  pid_t pid;
  int status;

  if (signal(SIGINT, sig_int) == SIG_ERR) {
    printf("signal error");
    exit(0);
  }

  printf("%% ");
  while(fgets(buf, MAXLINE, stdin) != NULL) {
    if(buf[strlen(buf) - 1] == '\n')
      buf[strlen(buf) - 1] = 0; /* replace newline with null */

    if ((pid = fork()) < 0) {
      printf("fork error");
    } else if (pid == 0) { /* child */
      execlp(buf, buf, (char*) 0); /* arguments are: executable file, the name of argv[0] (typically same as executable filename), then arguments for this executable followed by a null pointer. */
    }

    /* parent */
    if ((pid = waitpid(pid, &status, 0)) < 0)
      printf("waitpid error");

    printf("%% ");
  }

  exit(0);
}

void sig_int(int signo) {
  printf("interrupt%d\n%% ", signo);
}
