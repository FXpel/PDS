#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

/* On veut exécuter deux appels à la fonction « fonct » de façon
 * concurrente */

int fonct(char c, unsigned int nb) {
    unsigned int i;

    for (i = 0; i < nb; i++) {
        putchar(c);
    }

    return 1234;
}

struct fonct_args_s {
    char c;
    unsigned int nb;
};

void * fonct_wrapper(void *a) {
    struct fonct_args_s * fa = a;
    fonct(fa->c, fa->nb);
    return NULL;
}

int main() {
    /* fonct('|', 100000); */
    pthread_t thread_id;
    void * res;
    struct fonct_args_s fa;
    fa.c = '|';
    fa.nb = 100000;
    assert(pthread_create(&thread_id, NULL, &fonct_wrapper, &fa) == 0);

    fonct('.', 100000);

    assert(pthread_join(thread_id, &res) == 0);

    return 0;
}
