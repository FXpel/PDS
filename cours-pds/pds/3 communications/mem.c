#include <stdlib.h>

int main(int argc, char *argv[]) {
    /* int * ptr; */

    /* ptr = malloc(sizeof(int)); */
    system("bash");

    /* dans le shell qui est lancé, regarder la carte mémoire du
     * processus mem, soit en faisant :
     * $ cat /proc/$(pidof mem)/maps
     * soit en faisant :
     * $ ../outils/mem.sh $(pidof mem)
     */

    return 0;
}
