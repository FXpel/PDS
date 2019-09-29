#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

/* Commande qui indique si son argument désigne un fichier ordinaire
 * (plutôt qu’un répertoire, etc.) en utilisant stat(2) */

int main(int argc, char *argv[]) {
    struct stat *buf;
    struct stat buf2;
    int res;

    assert(argc > 1);

    /* printf("%ld\n", sizeof(struct stat *)); */
    /* printf("%ld\n", sizeof(struct stat)); */

    buf = malloc(sizeof(struct stat));
    assert(buf != NULL);

    res = stat(argv[1], buf);
    assert(res != -1);

    res = stat(argv[1], &buf2);
    assert(res != -1);

    if(S_ISREG(buf -> st_mode))
        printf("Fichier ordinaire\n");
    if(S_ISREG(buf2.st_mode))
        printf("Fichier ordinaire\n");

    free(buf);

    return 0;
}
