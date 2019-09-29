#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

/* Commande qui écrit un octet à la position absolue 1Go */

/* Si le fichier ne contient pas déjà 1Go de données (le fichier
 * n’existait pas avant, par exemple), crée un fichier creux (les
 * blocs d’octets nuls ne sont pas réellement écrits sur le disque) */

int main(int argc, char *argv[]) {
    int fd;
    off_t pos;
    int ecris;

    assert(argc > 1);
    fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0644);
    assert(fd != -1);

    pos = lseek(fd, 1 << 30, SEEK_SET);
    assert(pos != -1);

    /* Essayer avec et sans le write suivant */
    ecris = write(fd, "a", 1);
    assert(ecris != -1);

    close(fd);

    return 0;
}
