#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int FD = 1;
/* Ajouter  export MCAT_BUFSIZ=16 dans le terminal
*/
char* inverser(char tab[]){
	int i;
	int j=strlen(tab)-1;
	char temp;
	for (i = 0; i <j; ++i,j--)
	{
		temp = tab[i];
		tab[i] = tab[j];
		tab[j] = temp;
		
	}
	return tab;
	
}
int main(int argc, char *argv[])
{	
	struct stat st;
	int readc,taille,fd,stats;
	assert(argc>=1);
	printf("argv[1] vaut : %s \n",argv[1]);
	stats = stat(argv[1],&st);
	assert(stats==0);
	taille = atoi(getenv("MCAT_BUFSIZ"));
	char tab[taille];
    fd=open(argv[1],O_RDONLY);
    assert(fd != -1);
    
	while((readc = read(fd,&tab,taille))>0){
		sleep(1);
		inverser(tab);
		write(FD,tab,readc);
		
		
		
	}
	
	close(fd);
	return 0;
	
}

/*tamère*/
