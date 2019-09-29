/* Commande qui crée un fichier dans le répertoire /tmp et dont le nom
 * est donné en argument sur la ligne de commande
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int fd;
    char nom[256];

    assert(argc > 1);
    printf("%s\n", argv[0]);

    /* strcpy(nom, "/tmp/"); */
    /* strncat(nom, argv[1], 250); */

    snprintf(nom, 256, "/tmp/%s", argv[1]);

    fd = creat(nom, S_IRWXU);
    /* assert(fd != -1); */
    if(fd == -1) {
        perror("créer");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
