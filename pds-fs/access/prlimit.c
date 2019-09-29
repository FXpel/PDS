#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <assert.h>

void prlimit(){
	
	printf("La valeur de name est : %d\n",NAME_MAX);
	printf("La valeur de path est : %d\n",PATH_MAX);
    
}

int main()

{
	
	prlimit();
	return 0;
}
