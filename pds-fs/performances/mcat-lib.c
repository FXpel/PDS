#include <assert.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>




int main(int argc, char const *argv[])
{	
	
	FILE *fd;
   int readc;
  assert(argv[1]!=NULL);
   fd = fopen(argv[1],"r");
   assert(fd != NULL);
   assert(argc>=1);
   while(1==1){
      readc = fgetc(fd);
      if( feof(fd) ) {
         break ;
      }
      fputc(readc,stdout);
   } 

   fclose(fd);
   return(0);
	
}

