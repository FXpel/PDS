#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* Commande qui crée un nouveau processus
 *
 * Suivant les lignes commentées et décommentées, on peut notamment
 * voir les points suivants :
 *
 * - les deux processus, père et fils, s’exécutent en même temps,
 * - la valeur donnée en argument à exit est retournée au père
 * - le père peut, et doit, attendre la fin d’un fils et récupérer des
 *   informations sur comment s’est terminé le fils (exit ou non ; si
 *   exit, avec quelle valeur ; sinon, pour quelle raison (par exemple
 *   un segfault))
 * - la valeur transmise du fils au père par exit est un _octet_, pas
 *   un int complet
 * - entre la terminaison du fils et l’appel à wait dans le père, le
 *   fils est à l’état Zombie
 * - si le père se termine avant le fils, le fils est adopté par le
 *   processus de PID = 1, appelé « init »
 */

int main() {
    int status;
    pid_t pid, pid2;
    int *p = NULL;

    printf("Avant le fork : mon pid = %d\n", getpid());

    switch (pid = fork()) {
    case -1:
        exit(EXIT_FAILURE);

    case 0:                    /* Fils */
        printf("Je suis le fils : mon pid = %d, mon père = %d\n", getpid(), getppid());
        sleep(10);
        printf("Je suis le fils : mon pid = %d, mon père = %d\n", getpid(), getppid());

        /* Essayer chacune des lignes suivantes */
        /* Chacune termine le processus fils d’une façon différente */
        /* *p = 12; */
        /* exit(EXIT_SUCCESS); */
        exit(123);
        /* exit(1234); */

    default:                   /* Père */
        printf("Je suis le père : mon pid = %d, mon père = %d\n", getpid(), getppid());

        /* Pour voir apparaître l’état Zombie du fils, activer la
         * ligne suivante */
        /* sleep(3600); */

        /* Pour voir l’adoption du fils par init, activer la ligne suivante */
        /* sleep(5); exit(EXIT_SUCCESS); */

        pid2 = wait(&status);
        printf("Mon fils (%d) s’est terminé : status = %d\n", pid2, status);
        if (WIFEXITED(status)) {
            /* mon fils a fait exit */
            printf("Valeur de retour = %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Signal = %d\n", WTERMSIG(status));
        }
    }

    return 0;
}
