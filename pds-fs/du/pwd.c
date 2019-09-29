#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

int is_root(char* path){
  struct stat pathstat;
  struct stat rootstat;

  stat("/",&rootstat);
  assert(&rootstat!=NULL);
  stat(path,&pathstat);
  assert(&pathstat!=NULL);
  return rootstat.st_ino == pathstat.st_ino;
}

void print_name_in_parent(char* current, char* father){
  struct stat cur;

  DIR* dir;
  struct dirent* direntry;
  stat(current, &cur);
  assert(&cur!=NULL);
  dir = opendir(father);
  while((direntry = readdir(dir))){
    if((direntry->d_ino==cur.st_ino)){
      printf("%s",direntry-> d_name);
      break;
    }
    closedir(dir);
    return;
  }


}

void print_node_dirname(char* current){
  char father[PATH_MAX+1];
  if(is_root(current))
    return;
  strcpy(current,father);
  print_node_dirname(strcat(father,"/.."));
  printf("/");
  print_name_in_parent(current,father);



}

void pwd(){
  if(is_root(".")){
    printf(" / \n");
  }
  else {
    print_node_dirname(".");
  }
  return;
}

int main(int argc, char *argv[])
{
  
  printf(" %s\n");
  if (argc==2){
    pwd();
    print_node_dirname(argv[1]);
    printf("\n");
  }
  return 0;
}
