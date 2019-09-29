#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>


#define SIZE_OF_BUFFER 1

static const char* pathname;
static long ntail = 10;

int is_file(const char *pathname){
  struct stat st;
  int status;

  status = stat(pathname, &st);
  assert(status == 0);
  return S_ISREG(st.st_mode);
}


void analyse_args(int argc, const char * argv[]){
  assert(argc > 1);
  if(is_file(argv[1])){
    pathname = argv[1];
    if(argc > 2)
      ntail = abs(atoi(argv[3])); /* Apparemement deprecié pour strtoi */
  }
  else{
    perror("Ce n'est pas un fichier !");
    exit(EXIT_FAILURE);
  }
}


void print_buffer(const char* buffer, int bufsize){
    assert (write(STDOUT_FILENO, buffer, bufsize) !=-1);
}


int nlines_of_file(int df){
  int nlines = 0;
  char buffer[SIZE_OF_BUFFER];
  int nread_octet;
  while( (nread_octet = read(df, buffer, SIZE_OF_BUFFER)) != 0){
    assert(nread_octet != -1);
    if(buffer[0] == '\n'){
      nlines++;
    }
  }
  lseek(df,SEEK_SET, 0);
  return nlines;
}


void print_last_file(int df){
  int lignes_max = 0;
  int current_line = 0;
  char buffer[SIZE_OF_BUFFER];
  int nread_octet;
  lignes_max = nlines_of_file(df);
  while( (nread_octet = read(df, buffer, SIZE_OF_BUFFER)) != 0){
    assert(nread_octet != -1);
    if( (lignes_max - ntail <= 0) || (current_line >= (lignes_max - ntail)) ){
      print_buffer(buffer, nread_octet);
    }
    if(buffer[0] == '\n'){
      current_line++;
    }
  }
}

void tail(){
  int df;
  df = open(pathname, O_RDONLY);
  assert(df != -1);
  print_last_file(df);
}

int main(int argc,const char* argv[]) {
  analyse_args(argc, argv);
  tail();
  return EXIT_SUCCESS;
}
