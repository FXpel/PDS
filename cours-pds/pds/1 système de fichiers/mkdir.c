#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <assert.h>

/* Petite commande qui crée un répertoire (comme la commande mkdir
 * elle-même, d’ailleurs) */

int main(int argc, char *argv[]) {
    int res;

    assert(argc > 1);

    res = mkdir(argv[1], S_IRUSR | S_IWUSR | S_IXUSR
                       | S_IRGRP | S_IWGRP | S_IXGRP
                       | S_IROTH | S_IWOTH | S_IXOTH);
    /* Ces droits peuvent être limités par umask (voir la page de
     * manuel de mkdir et celle d’umask */
    assert(res != -1);

    return EXIT_SUCCESS;
}
