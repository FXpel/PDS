#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>

static int nb_threads = 1;
struct gc_s{
  char *bloc;
  unsigned long taille;
  unsigned long result;
};

unsigned long compteur_gc(char *bloc, unsigned long taille) {
    unsigned long i, cptr = 0;

    for (i = 0; i < taille; i++)
        if (bloc[i] == 'G' || bloc[i] == 'C')
            cptr++;

    return cptr;
}

void* wrapper(void* arg){
  struct gc_s  *g = (struct gc_s *)arg;
  g->result = compteur_gc(g->bloc,g->taille);
  return NULL;
}

int main(int argc, char *argv[]) {
    struct stat st;
    struct gc_s *stgc;
    pthread_t* t;
    int status;
    int fd;
    char *tampon;
    int lus;
    unsigned long cptr = 0;

    off_t taille = 0;
    struct timespec debut, fin;
    nb_threads = atoi(argv[2]);
    stgc = (struct gc_s*)malloc(nb_threads*sizeof(struct gc_s));
    t = (pthread_t*)malloc(nb_threads*sizeof( pthread_t));
    assert(argc > 1);

    /* Quelle taille ? */
    assert(stat(argv[1], &st) != -1);
    tampon = malloc(st.st_size);
    assert(tampon != NULL);

    /* Chargement en mémoire */
    fd = open(argv[1], O_RDONLY);
    assert(fd != -1);
    while ((lus = read(fd, tampon + taille, st.st_size - taille)) > 0)
        taille += lus;
    assert(lus != -1);
    assert(taille == st.st_size);
    close(fd);
    /* Calcul proprement dit */
    assert(clock_gettime(CLOCK_MONOTONIC, &debut) != -1);
    for(int i =0; i< nb_threads;i++){
      stgc[i].taille = taille/nb_threads;
      stgc[i].bloc = tampon+i*(taille/nb_threads);
      status = pthread_create(t+i,NULL,wrapper,stgc+i);
      assert(status == 0);

    }
    for(int z = 0; z < nb_threads; z++){
      status = pthread_join(t[z],NULL);
      assert(status == 0);
      cptr += stgc[z].result;
    }
    
    assert(clock_gettime(CLOCK_MONOTONIC, &fin) != -1);

    /* Affichage des résultats */
    printf("Nombres de GC:   %ld\n", cptr);
    printf("Taux de GC:      %lf\n", ((double) cptr) / ((double) taille));

    fin.tv_sec  -= debut.tv_sec;
    fin.tv_nsec -= debut.tv_nsec;
    if (fin.tv_nsec < 0) {
        fin.tv_sec--;
        fin.tv_nsec += 1000000000;
    }
    printf("%ld.%09ld\n",fin.tv_sec,fin.tv_nsec);
    /*printf("Durée de calcul: %ld.%09ld\n", fin.tv_sec, fin.tv_nsec);
    printf("(Attention: très peu de chiffres après la virgule sont réellement significatifs !)\n");*/

    return 0;
}
