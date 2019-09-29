#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    sigset_t masque;
    int r;

    assert(sigemptyset(&masque) == 0);
    assert(sigaddset(&masque, SIGINT) == 0);
    r = sigprocmask(SIG_BLOCK, &masque, NULL);
    assert(r != -1);

    while(1) {
        pause();
        printf("beep\n");
    }

    return 0;
}
