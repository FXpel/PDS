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
	
	int readc;
	int taille; 
	int fd ; 
	assert(argc>=1);
	assert(argv[1]!=NULL);
	taille = atoi(getenv("MCAT_BUFSIZ"));
	char tab[taille];
    fd=open(argv[1],O_RDONLY);
    assert(fd != -1);
	while((readc = read(fd,&tab,taille))>0){
		
		write(FD,&tab,readc);
		
	}
	close(fd);
	return 0;
}

