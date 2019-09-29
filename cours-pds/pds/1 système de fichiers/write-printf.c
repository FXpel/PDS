#include <assert.h>
#include <stdio.h>
#include <unistd.h>

/* Commande qui illustre l’existence de tampon mémoire dans
 * l’interface FILE utilisée par fprintf, contrairement aux appels
 * systèmes (read, write) */

int main() {
    int ecris;

    ecris = write(STDOUT_FILENO, "a", 1);
    assert(ecris != -1);

    /* printf("b"); est équivalent à fprintf(stdout, "b"); */
    fprintf(stdout, "b");

    /* Essayer avec et sans la ligne suivante */
    /* fflush(stdout); */

    ecris = write(STDOUT_FILENO, "c", 1);
    assert(ecris != -1);

    return 0;
}
