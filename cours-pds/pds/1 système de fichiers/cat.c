#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#define TAILLE 16

/* Commande qui affiche sur la sortie standard le contenu de son
 * premier argument (fichier ordinaire) */

int main(int argc, char *argv[]) {
    int fd_lect;
    char tampon[TAILLE];
    int lus;
    /* int i; */

    assert(argc > 1);

    fd_lect = open(argv[1], O_RDONLY);
    assert(fd_lect != -1);

    while ( (lus = read(fd_lect, tampon, TAILLE)) > 0 ) {
        /* Attention : tampon n’est pas une chaîne de caractères */
        /* printf("%s", tampon); */

        /* for(i = 0; i < lus; i++) */
        /*     printf("%c", tampon[i]); */

        assert(write(STDOUT_FILENO, tampon, lus) == lus);
    }

    assert(lus != -1);

    close(fd_lect);

    return 0;
}
