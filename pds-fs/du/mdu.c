#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <getopt.h>
#include <limits.h>
#include <assert.h>
#include <ctype.h>

static int opt_follow_link=0;
static int opt_apparent_size=0;

int is_valid_name(char *dname){
	if((strcmp(dname,".")==0)||(strcmp(dname,"..")==0))
		return 0;

	else
		return 1;

}

int du_file(const char *pathname){
	struct stat pathstat;
	DIR *dir;
	struct dirent *direntry;
	int size=0;
	int status;
	char path_entry[PATH_MAX+1];



	if(opt_follow_link){
		status = stat(pathname,&pathstat);
	}
	else
		status = lstat(pathname,&pathstat);
	assert(status==0);
    if (opt_apparent_size)
        size= pathstat.st_size;


     else {
        size= pathstat.st_blocks;
}



	/*vérification fichier ordinaire */
	if(S_ISREG(pathstat.st_mode))
		return size;

	/*vérification fichier répertoire */
	if(S_ISDIR(pathstat.st_mode)){
		dir =opendir(pathname);
		while((direntry=readdir(dir))!=NULL){
			if(is_valid_name(direntry->d_name)){
            snprintf(path_entry,PATH_MAX,"%s/%s",pathname,direntry->d_name);

            size+=du_file(path_entry);

            }

		}
		closedir(dir);


	}
	return size;
}

int main(int argc, char * const argv[])
{
	char * pathname;

	int c;
	int _b=0;
	int _L=0;

	opterr=0;
	while ((c=getopt(argc,argv,"bL"))!=-1){
		switch(c){
			case 'b':
				_b=1;
				break;
			case 'L':
				_L=1;
				break;
			case '?':
				fprintf(stderr, "Invalid option -- '%c'.\n", optopt);
                    return EXIT_FAILURE;
            default:
            	opt_apparent_size=512;

		}
	}
	if(_b==1)
        opt_apparent_size=1;
    if(_L==1)
        opt_follow_link=1;

    pathname=argv[optind];

	printf("%d\t%s\n",du_file(pathname),pathname);
	return 0;
}
