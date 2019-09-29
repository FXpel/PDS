#include <stdio.h>
#include <pthread.h>
#include <assert.h>

#define ITER 1000000

int c1, c2, c3;

pthread_mutex_t mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
/* Comparer avec : */
/* pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; */

void *th_compteur(void *arg) {
    int i;

    for (i = 0; i < ITER; i++) {
        assert(pthread_mutex_lock(&mutex) == 0);
        assert(pthread_mutex_lock(&mutex) == 0);
        c1++;
        assert(pthread_mutex_unlock(&mutex) == 0);
        assert(pthread_mutex_unlock(&mutex) == 0);
        c2++;
    }
    return NULL;
}

int main() {
    pthread_t tid;
    int i;

    assert(pthread_create(&tid, NULL, th_compteur, NULL) == 0);

    for (i = 0; i < ITER; i++) {
        assert(pthread_mutex_lock(&mutex) == 0);
        c1++;
        assert(pthread_mutex_unlock(&mutex) == 0);
        c3++;
    }

    assert(pthread_join(tid, NULL) == 0);

    printf("%d + %d = %d = %d\n", c2, c3, c2 + c3, c1);

    return 0;
}
