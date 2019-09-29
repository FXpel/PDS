#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void hello(int sig) {
    printf("Hello (%d)\n", sig);
}

int main() {
    int i;
    struct sigaction sa;

    sa.sa_handler = &hello;
    sa.sa_flags = 0;
    assert(sigemptyset(&sa.sa_mask) == 0);

    for (i = 1; i < 32; i++) {
        if(i == SIGKILL || i == SIGSTOP) continue;
        assert(sigaction(i, &sa, NULL) == 0);
    }

    for (i = 1; i < 32; i++) {
        if(i == SIGKILL || i == SIGSTOP) continue;
        fprintf(stderr, "Je m’envoie le signal %d\n", i);
        raise(i);
    }

    return 0;
}
