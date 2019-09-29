#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void enfants(int sig) {
    static int compteur = 0;

    compteur++;
    printf("%d-eme enfant terminé\n", compteur);
}

int main(int argc, char *argv[]) {
    long int nb;
    struct sigaction sa;

    sa.sa_handler = &enfants;
    sa.sa_flags = 0;
    assert(sigemptyset(&sa.sa_mask) == 0);
    assert(sigaction(SIGCHLD, &sa, NULL) == 0);

    assert(argc > 1);
    nb = strtol(argv[1], NULL, 10);
    for (; nb > 0; nb--) {
        switch (fork()) {
            case -1:
                exit(EXIT_FAILURE);

            case 0:
                printf("Fils %d\n", getpid());
                exit(EXIT_SUCCESS);
        }
    }

    while(1)
        wait(NULL);

    return 0;
}
