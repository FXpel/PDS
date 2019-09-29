#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

#define TAILLE 16

/* Commande qui copie un fichier ordinaire (son premier argument) vers
 * son deuxième argument */

int main(int argc, char *argv[]) {
    int fd_lect, fd_ecr;
    char tampon[TAILLE];
    int lus, ecris;

    assert(argc > 2);

    fd_lect = open(argv[1], O_RDONLY);
    assert(fd_lect != -1);
    fd_ecr = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644);
    assert(fd_ecr != -1);

    while ( (lus = read(fd_lect, tampon, TAILLE)) > 0 ) {
        ecris = write(fd_ecr, tampon, lus);
        assert(ecris == lus);
    }
    assert(lus != -1);

    close(fd_lect);
    close(fd_ecr);

    return 0;
}
