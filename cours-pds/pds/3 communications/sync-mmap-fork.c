#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int main() {
    int *ptr;

    /* ptr = malloc(sizeof(int)); */
    /* assert(ptr != NULL); */

    ptr = mmap(NULL, sizeof(int),
               PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    assert(ptr != MAP_FAILED);

    printf("Avant : %d\n", *ptr);

    switch (fork()) {
    case -1:
        exit(EXIT_FAILURE);

    case 0:                    /* Fils */
        *ptr = 1234567890;
        exit(EXIT_SUCCESS);
    }

    sleep(1);
    printf("Après : %d\n", *ptr);

    return 0;
}
