#include <stdio.h>
#include <pthread.h>
#include <assert.h>

#define ITER 1000000

/* Les variables suivantes sont partagées par les différents threads */
int c1, c2, c3;

void *th_compteur(void *arg) {
    int i;

    for (i = 0; i < ITER; i++) {
        c1++;
        c2++;
    }
    return NULL;
}

int main() {
    pthread_t tid;
    int i;

    assert(pthread_create(&tid, NULL, th_compteur, NULL) == 0);

    for (i = 0; i < ITER; i++) {
        c1++;
        c3++;
    }

    assert(pthread_join(tid, NULL) == 0);

    printf("%d + %d = %d = %d\n", c2, c3, c2 + c3, c1);

    return 0;
}
