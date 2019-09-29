#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int * ptr;
    char cmd[1000];

    snprintf(cmd, 1000, "../outils/mem.sh %d", getpid());
    printf("Avant mmap\n");
    system(cmd);

    ptr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
               MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    assert(ptr != MAP_FAILED);

    printf("mmap a retourné : %p\n", (void*)ptr);
    printf("Après le mmap\n");
    system(cmd);

    return 0;
}
