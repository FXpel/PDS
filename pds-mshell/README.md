#   Gestionnaire de travaux

Ce dépôt correspond au TP de PDS
« [mshell](http://www.fil.univ-lille1.fr/~hym/e/pds/tp/tdjobs.html) ».
Il contient un canevas de départ pour votre gestionnaire de travaux.
Vous y trouverez notamment :

-   un `Makefile` ;
-   `mshell.c` : contient entre autres le `main()` ;
-   `cmd.c`, `cmd.h` : contient les commandes `fg`, `bg`, `stop`...
-   `jobs.c`, `jobs.h` : contient la bibliothèque gérant les
    structures de données associées aux jobs ;
-   `sighandlers.c`, `sighandlers.h` : contient les traitants de
    signaux ;
-   `common.c`, `common.h` : contient des données et fonctions
    communes aux différents fichiers.

Dans un premier temps, vous n’aurez qu’à modifier les fichiers `cmd.c`
et `sighandlers.c`.
Les squelettes des fonctions à implémenter sont déjà donnés ; aucune
autre fonction n’est nécessaire.

Le mini-shell peut fonctionner en mode _verbose_ (`mshell -v`) ce qui
permet d’avoir des informations sur les traitants et fonctions
sollicités, etc. Une variable globale _verbose_ est prévue à cet effet.
Pensez à l’utiliser ! Le fichier `jobs.c` contient un exemple de son
utilisation, à vous de voir selon les situations quelles informations
afficher.

Pour l’instant la compilation du `mshell` affiche quelques
avertissements dus au code manquant. Vous devrez pouvoir justifier
ceux qui resteront à la fin de votre travail.


##  Instructions pour rendre votre travail avec gitlab

Pour permettre à votre chargé de TD de suivre votre travail sur ce projet :

-   *forkez* ce dépôt (bouton _Fork_),
-   dans le dépôt *forké*, ajoutez votre chargé de TD aux membres du
    projet avec l’accès _Developer_,
-   éditez ce fichier `README.md` pour indiquez vos noms (membres du
    binôme) et supprimer ce paragraphe d’instructions.


##  Intégration continue (CI)

Si vous trouvez que l’intégration continue vous aide à savoir où vous en
êtes, vous pouvez créer un fichier `.gitlab-ci.yml` contenant par
exemple :

```yaml
image: commonci-fil:latest

build:
  script: make strict
```

Vous pouvez bien entendu utiliser d’autres tests que celui-là.
