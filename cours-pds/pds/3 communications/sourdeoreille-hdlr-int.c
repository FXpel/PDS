#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void ignore(int sig) {
    printf("même pas mal\n");
}

int main() {
    struct sigaction sa;

    sa.sa_handler = &ignore;
    sa.sa_flags = 0;
    assert(sigemptyset(&sa.sa_mask) == 0);
    assert(sigaction(SIGINT, &sa, NULL) == 0);

    while(1) {
        pause();
        printf("beep\n");
    }

    return 0;
}
