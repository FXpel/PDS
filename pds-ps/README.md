#   Gestion des processus

Ce dépôt correspond aux TPs de PDS « [Gestion des processus](http://www.fil.univ-lille1.fr/~hym/e/pds/tp/tdps.html) ».


##  Instructions pour rendre votre travail avec gitlab

Pour permettre à votre chargé de TD de suivre votre travail sur ce projet :

-   *forkez* ce dépôt (bouton _Fork_),
-   dans le dépôt *forké*, ajoutez votre chargé de TD aux membres du
    projet avec l’accès _Developer_,
-   éditez ce fichier `README.md` pour indiquer vos noms (membres du
    binôme) et supprimer ce paragraphe d’instructions.


##  Intégration continue (CI)

Ce dépôt est configuré (vous pouvez regarder le fichier
`.gitlab-ci.yml`) pour utiliser le système d’intégration continue.
À chaque fois que vous pousserez un commit sur le serveur, votre
travail sera compilé et quelques tests déclenchés.
Tous les voyants devraient progressivement passer au vert (il est
normal que les compilations échouent tant que vous n’avez pas commencé
à écrire les programmes, bien entendu…).
