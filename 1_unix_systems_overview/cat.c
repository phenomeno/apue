#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFSIZE 4096

int main(void) {
    int n;
    char buf[BUFFSIZE];

    // STDIN_FILENO is the file descriptor for std in (0), which is connected to terminal by default by shell. will read in what we write to that fd
    // STDOUT_FILENO is the fd for std out (1)
    while((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
        if (write(STDOUT_FILENO, buf, n) != n)
            printf("write error");

    if (n < 0)
        printf("read error");

    exit(0);
}
