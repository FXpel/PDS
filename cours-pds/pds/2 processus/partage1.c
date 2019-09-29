#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* Partage ? */
/* Est-ce que la variable i est partagée entre les deux processus ? */

int main() {
    int status;
    pid_t pid, pid2;
    int i = 123;

    printf("Avant le fork : mon pid = %d\n", getpid());
    printf("Avant le fork, i = %d\n", i);

    printf("avant");

    switch (pid = fork()) {
    case -1:
        exit(EXIT_FAILURE);

    case 0:                    /* Fils */
        printf("Je suis le fils : mon pid = %d, mon père = %d\n", getpid(), getppid());
        sleep(5);
        printf("Je suis le fils : mon pid = %d, mon père = %d\n", getpid(), getppid());
        printf("Dans le fils, i = %d\n", i);

        exit(EXIT_SUCCESS);

    default:                   /* Père */
        printf("Je suis le père : mon pid = %d, mon père = %d\n", getpid(), getppid());

        i++;
        printf("Dans le père, i = %d\n", i);

        pid2 = wait(&status);
        assert(pid == pid2);
        printf("Mon fils (%d) s’est terminé\n", pid2);
        printf("Dans le père, i = %d\n", i);
    }

    return 0;
}
