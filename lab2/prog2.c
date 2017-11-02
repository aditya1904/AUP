#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[]){
	int r, n;
	char dname[16], ftmp[16], fname[16], linkpar[64];
	struct stat st;
	mode_t mode;
	DIR *dir;
	struct dirent *ent;

	if(argc > 1)
		strcpy(dname, argv[1]);
	else
		strcpy(dname, ".");

	strcpy(fname, dname);
	strcat(fname, "/");

	dir = opendir(dname);
	if(!dir){
		printf("Error opening directory\n");
		return 0;
	}
	while((ent = readdir(dir)) != NULL){
		if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0){
			strcpy(ftmp, fname);
			strcat(ftmp, ent->d_name);
			lstat(ftmp, &st);

			if(S_ISLNK(st.st_mode)){								
				printf("%s : ", ftmp);
				while(S_ISLNK(st.st_mode)){								
					r = readlink(ftmp, linkpar, 63);
					if(r == -1){
						printf("Link broken\n");
						break;
					}
					linkpar[r] = '\0';

					strcpy(ftmp, linkpar);
					lstat(ftmp, &st);
				}
				printf("%s\n", ftmp);
			}
		}
	}
}
