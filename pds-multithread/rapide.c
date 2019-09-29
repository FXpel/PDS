#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "pile.h"
#include "tri.h"
#include "rapide.h"
#include "main.h"

#define SIZE 1024
unsigned long seuil_bloc_long = 1;

pthread_mutex_t m ;

base_t *tableau;

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
pthread_mutex_t fastmutex =PTHREAD_MUTEX_INITIALIZER ;
pthread_cond_t cd;

/* etape elementaire du tri rapidee: decoupe le bloc b en 0, 1 ou 2 blocs
 * Dans le cas normal, decoupe en 2 blocs, les elements inferieurs au
 * pivot, et ceux superieurs au pivot
 * Si un bloc contient moins de 1 element, il n'est pas retourne
 */
int rapide_decoupebloc(bloc_t b, bloc_t bret[2]) {
    pos_t g, d;
    base_t pivot, tmp;
    bloc_t b1, b2;
    int nb_ret = 0;

    if(b.debut >= b.fin) {
        /* Arrive uniquement dans le cas d'un tri d'un tableau de
         * taille 1 au depart */
        assert (b.debut == b.fin);
        return 0;
    }

    /* Definit une petite macro pour echanger deux cases de tableau en
     * passant par la variable tmp */
#define echange(p1,p2)                     \
    do {                                   \
        tmp         = tableau[p1];         \
        tableau[p1] = tableau[p2];         \
        tableau[p2] = tmp;                 \
    } while(0)

    pivot = tableau[b.debut];
    g = b.debut + 1;
    d = b.fin;

    while (g < d) {
        while (g < d && tableau[g] <= pivot)
            g++;
        while (d > g && tableau[d] > pivot)
            d--;
        if (g < d)
            echange(g, d);
    }

    b1.debut = b.debut;
    b2.fin = b.fin;

    if (tableau[g] <= pivot) {
        echange(g, b.debut);
        b1.fin   = g - 1;
        b2.debut = min(g + 1, b2.fin);
    } else if (g > b.debut + 1) {
        echange(g - 1, b.debut);
        b1.fin   = max(g - 2, b1.debut);
        b2.debut = g;
    } else {                    /* sinon le pivot est le plus petit, donc deje bien place */
        b1.fin   = b.debut;
        b2.debut = b.debut + 1;
    }

    if (b1.debut < b1.fin)
        bret[nb_ret++] = b1;
    if (b2.debut < b2.fin)
        bret[nb_ret++] = b2;

    return nb_ret;
}

/* Effectue un tri rapide sequentiel */
void rapide_seq(bloc_t bloc_init) {
    pile p;
    int i, nb_blocs;
    bloc_t bloc;
    bloc_t blocs[2];

    init_pile(&p);
    empile(&p, bloc_init);

    /* Principe du tri rapide sequentiele:
     * tant qu'il y a des blocs e trier, depile un bloc, le decoupe en
     * (au maximum) deux sous-blocs non-encore tries et les empile */
    do {
        bloc = depile(&p);
        nb_blocs = rapide_decoupebloc(bloc, blocs);
        for (i = 0; i < nb_blocs; i++)
            empile(&p, blocs[i]);
    } while (!pile_vide(&p));
}

void * rapide_thr (void * arg) {
  pile p = *((pile *)arg) ;
  static int nb_thread_actif = 0 ;
  int i, nb_blocs ;
  bloc_t bloc ;
  bloc_t blocs[2] ;

  do {
    pthread_mutex_lock (&m) ;
    bloc = depile(&p);
    nb_thread_actif++ ;
    i = pile_vide(&p) ;
    if (!i) // Si la pile est vide on empeche les autres threads d'y acceder
      pthread_mutex_unlock (&m) ; // le temps de rempiler

    nb_blocs = rapide_decoupebloc(bloc, blocs);

    if (!i) // Si on a pas debloque on ne bloque pas
      pthread_mutex_lock (&m) ;
    nb_thread_actif-- ;
    for (i = 0 ; i < nb_blocs ; i++) {
      if ((unsigned int) blocs[i].fin < seuil_bloc_long)
    rapide_seq(blocs[i]) ;
      else
    empile(&p, blocs[i]) ;
    }
    pthread_mutex_unlock (&m) ; // on debloque quoi qu'il arrive

  } while (!pile_vide(&p) && (nb_thread_actif == 0)) ;

  return NULL ;
}

void rapide_mt (bloc_t bloc_init, unsigned int nb_thread) {
    pile p ;
    unsigned int i ;
    pthread_t * threads ;

    threads = malloc (sizeof(pthread_t) * nb_thread) ;

    init_pile(&p) ;
    empile(&p, bloc_init) ;

    if (pthread_mutex_init (&m, NULL) != 0) {
      fprintf (stderr, "mutex init failed !\n") ;
      exit (EXIT_FAILURE) ;
    }

    for (i = 0 ; i < nb_thread ; i++)
      pthread_create (&threads[i], NULL, rapide_thr, &p) ;

    for (i = 0 ; i < nb_thread ; i++)
      pthread_join (threads[i], NULL) ;

    pthread_mutex_destroy (&m) ;
    free(threads) ;

}

void rapide(pos_t taille, unsigned int nb_threads) {
    bloc_t bloc;

    bloc.debut = 0 ;
    bloc.fin   = taille - 1 ;

    if (nb_threads == 1||taille<SIZE) {
        rapide_seq(bloc);
        return;
    }

    assert(nb_threads > 1) ;

    rapide_mt (bloc, nb_threads) ;


}
