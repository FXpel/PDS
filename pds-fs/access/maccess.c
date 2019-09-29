#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int vflag, rflag, wflag, xflag;

void usage (char *prog) {
   printf("usage : %s [rvwx] file", prog);
}

void printVerbose()  {
  switch(errno) {
		case EACCES:
		perror("L'acces au fichier est refuse");
		break;

		case ELOOP:
		perror("Le fichier pointe sur trop de liens symbolique");
		break;

		case ENAMETOOLONG:
		perror("Le pathname est trop long");
		break;

		case ENOENT:
		perror("L'un des composant du chemin d'acces n'existe pas ou est un liens symbolique pointant nulle part");
		break;

		case ENOTDIR:
		perror("L'un des elements du chemin d'acces n'est pas un repertoire");
		break;

		case ETXTBSY:
		perror("Erreur produite car demande d'écriture dans un fichier exécutable qui est en cours d'utilisation");
		break;

		default:
		printf("%s\n", "Vous avez les droits");

	}
}

int maccess (int argc, char **argv) {
   int mode = 0;

   /*    On vérifie qu'au moins une option de vérification d'accès a été renseignée.
      Sinon, on arrête le programme.
   */

      if (rflag)
         mode |= R_OK;
      if (wflag)
         mode |= W_OK;
      if (xflag)
         mode |= X_OK;

   printf(" La valeur de access est : %d\n",access(argv[0],mode) );
      if (vflag)
          printVerbose();

      else{
          perror("Erreur dans l'utilisation des modes\n");
          exit(EXIT_FAILURE);
        }
   /*    On exécute la fonction access();
    */
   return access(argv[1],mode);
}

int main (int argc, char **argv) {
   int ch;
   vflag = 0;
   rflag = 0;
   wflag = 0;
   xflag = 0;
   while ((ch = getopt(argc, argv, "vrwxh")) != -1) {
      switch (ch) {
      case 'v':
         vflag = 1;
         break;
      case 'r':
         rflag = 1;
         break;
      case 'w':
         wflag = 1;
         break;
      case 'x':
         xflag = 1;
         break;
      case 'h':
      default:
         usage(argv[0]);
      }
   }
   argc -= optind;
   argv += optind;
   return maccess(argc,argv);
}
