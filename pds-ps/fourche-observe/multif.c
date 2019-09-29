#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


typedef int (*func_t) (char *);
int multif (func_t f[], char *args[], int n);

/*
si son argument est la chaîne "true", elle retourne EXIT_SUCCESS,
si son argument est la chaîne "false", elle retourne EXIT_FAILURE. 
*/
int testfunc(char * s ){
	if (strcmp(s,"true")==0)
		return EXIT_SUCCESS ;
	else
		return EXIT_FAILURE;
}

int multif (func_t f[], char *args[], int n) {

int i ;
pid_t pid ;
int t;
int res = !EXIT_SUCCESS;

for (i = 0; i < n; ++i)
{
	pid=fork();
	switch(pid) {
		case -1 :
		perror("Erreur fork ");
		exit(EXIT_FAILURE);
		break;
		case 0 :
		
		exit(f[i](args[i])); 
		break;
		default:
		;
	}
}
for (i=0; i<n; i++) {
	wait(&t);
	res = res && !t; /**/
}
return !res;
}


int main(int argc, char  **argv){
int i,var;
func_t *t;
t= (func_t *) malloc(sizeof(func_t)*argc-1);
for (i = 0;i<argc-1;i++){
	t[i]=testfunc;
}
var=multif(t,argv+1,argc-1);
printf("La valeur de multif est : %d\n",var);
exit(multif(t,argv+1,argc-1));
}
