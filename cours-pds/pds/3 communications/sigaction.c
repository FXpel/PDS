#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void hello(int sig) {
    printf("Hello (%d)\n", sig);
}

int main() {
    struct sigaction sa;

    sa.sa_handler = &hello;
    sa.sa_flags = 0;
    assert(sigemptyset(&sa.sa_mask) == 0);
    assert(sigaction(SIGINT, &sa, NULL) == 0);

    while(1) {
        pause();
        printf("Pause terminée\n");
    }

    return 0;
}
