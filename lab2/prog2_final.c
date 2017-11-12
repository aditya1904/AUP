#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<ctype.h>
#include<dirent.h>
#include<string.h>
int main(int argc, char *argv[]){
	struct stat fileStat;
	DIR *d;
	struct dirent *dir;
	char path[128];
	char buff[128];
	if(argc > 1)
		strcpy(path,argv[1]);
	else
		strcpy(path,".");
	d = opendir(path);
	if(d){
		while((dir = readdir(d)) != NULL){
			if(strcmp(dir->d_name,".") != 0 && strcmp(dir->d_name,"..") != 0){
				char new_path[128];
				strcpy(new_path,path);
				strcat(new_path,"/");
				strcat(new_path,dir->d_name);
				lstat(new_path,&fileStat);

				if(S_ISLNK(fileStat.st_mode)){
					printf("%s ",new_path);
					int tmp = readlink(new_path,buff,127);
					if(tmp == -1){
						printf("Linked failed..!!\n");
						break;
					}
					buff[tmp] = '\0';
					strcpy(new_path,buff);
					lstat(new_path,&fileStat);
					printf("%s\n",new_path);
				}
			}
		}
		closedir(d);
	}
return 0;
}