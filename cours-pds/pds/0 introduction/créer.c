/* Commande qui crée un fichier /tmp/test
 * On utilise pour cela l’appel système creat
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main() {
    int fd;

    fd = creat("/tmp/test", S_IRWXU);
    /* assert(fd != -1); */
    if(fd == -1) {
        perror("créer");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
