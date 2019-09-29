#   Processus légers

Ce dépôt correspond au TP de PDS « [Applications à des exemples
concrets](http://www.fil.univ-lille1.fr/~hym/e/pds/tp/tdth-concrets.html) ».


##  Instructions pour rendre votre travail avec gitlab

Pour permettre à votre chargé de TD de suivre votre travail sur ce projet :

-   *forkez* ce dépôt (bouton _Fork_),
-   dans le dépôt *forké*, ajoutez votre chargé de TD aux membres du
    projet avec l’accès _Developer_,
-   éditez ce fichier  pour indiquez vos noms (membres du
    binôme) et supprimer ce paragraphe d’instructions.


##  Contenu initial du dépôt

Ce répertoire contient deux squelettes de code.


### Calcul du taux G / C

`compteur-gc.c`
:   base pour le compteur de bases G et C

`aleazard.c`
:   générateur d’un « génome » aléatoire


### Tri rapide multithreadé

`pile.[ch]`
:   implémentation simple d’une pile,

`tri.[ch]`
:   fonctions de base permettant de charge ou afficher un tableau
    ainsi que vérifier qu’un tableau est trié,

`rapide.[ch]`
:   implémentation du tri rapide séquentiel, où vous ajouterez votre
    implémentation multithreadé,

`main.[ch]`
:   une fonction `main`, avec un `getopt` pour toute une série
    d’options qui vous aideront à tester et mettre au point votre
    code.
Voici le resultat :
![](resultat.png)

### Auteurs
  Adeniss Karti et François-Xavier Pelage
