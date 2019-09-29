#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <assert.h>

#define ITER 1000000

int c1, c2, c3;
sem_t sem;

void *th_compteur(void *arg) {
    int i;

    for (i = 0; i < ITER; i++) {
        assert(sem_wait(&sem) != -1);
        c1++;
        assert(sem_post(&sem) != -1);
        c2++;
    }
    return NULL;
}

int main() {
    pthread_t tid;
    int i;

    sem_init(&sem, 0, 1);

    assert(pthread_create(&tid, NULL, th_compteur, NULL) == 0);

    for (i = 0; i < ITER; i++) {
        assert(sem_wait(&sem) != -1);
        c1++;
        assert(sem_post(&sem) != -1);
        c3++;
    }

    assert(pthread_join(tid, NULL) == 0);

    printf("%d + %d = %d = %d\n", c2, c3, c2 + c3, c1);

    return 0;
}
