#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/* Commande qui teste s’il est possible de déplacer la tête de lecture
 *
 * Essayer :
 * $ ./seek2
 * $ ./seek2 < seek2.c
 * et interpréter les résultats */

int main() {
    off_t pos;

    pos = lseek(STDIN_FILENO, 0, SEEK_CUR);
    if(pos == -1) {
        perror("seek2");
        exit(EXIT_FAILURE);
    }

    return 0;
}
