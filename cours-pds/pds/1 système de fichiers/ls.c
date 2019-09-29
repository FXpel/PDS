#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>

/* Commande qui affiche toutes les entrées d’un répertoire
 * Si une entrée est un lien symbolique, affiche aussi la cible du
 * lien */

#define TAILLE 1024

int main(int argc, char *argv[]) {
    DIR *rep;
    struct dirent *de;
    int res;
    struct stat st;
    char cible[TAILLE];
    char chemin[PATH_MAX];

    assert(argc > 1);

    rep = opendir(argv[1]);
    assert(rep != NULL);

    while( (de = readdir(rep)) != NULL ) {
        printf("%ld %s", de->d_ino, de->d_name);
        fflush(stdout);

        snprintf(chemin, PATH_MAX, "%s/%s", argv[1], de->d_name);

        res = lstat(chemin, &st);
        /* Comparer avec */
        /* res = stat(de->d_name, &st); */
        assert(res != -1);
        if(S_ISLNK(st.st_mode)) {
            res = readlink(chemin, cible, TAILLE-1);
            assert(res != -1);
            cible[res] = '\0';
            printf(" -> %s", cible);
        }
        printf("\n");
    }

    res = closedir(rep);
    assert(res != -1);

    return 0;
}
