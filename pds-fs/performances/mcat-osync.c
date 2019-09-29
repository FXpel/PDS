#include <assert.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int FD = 1;
/* Ajouter  export MCAT_BUFSIZ=16 dans le terminal
*/
int main(int argc, char const *argv[])
{
  
   int readc,taille,fd;
   taille = atoi(getenv("MCAT_BUFSIZ"));
   char tab[taille];
    assert(argv[1]!=NULL);
    fd=open(argv[1],O_RDONLY);
    assert(fd != -1);
    fsync(fd);
    assert(fd != -1);
    assert(argc>1);
   while((readc = read(fd,&tab,taille))>0){
      

      write(FD,&tab,readc);

      
   }
   close(fd);
   return 0;
}

