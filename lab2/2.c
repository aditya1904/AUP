#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<linux/limits.h>
int checkifsymlink(char *str){
	struct stat statbuff;
	if(stat(str, &statbuff) != -1){
		if(!S_ISLNK(statbuff.st_mode)){
			return 1;
		}
	}
	return 0;
}

int main(int argc, char*argv[]){
	char str[PATH_MAX];
	struct stat statbuff;
	DIR *dp;
	struct dirent *ed;
	char a[PATH_MAX] = "./";
	if(argc >= 2){
		strcpy(a, argv[2]);
	}
	dp = opendir(a);

	if(dp != NULL){
		while(ed = readdir(dp)){
			if(argc < 2){
				if(checkifsymlink(strcat(a, ed->d_name))){
					printf("%s\n", realpath(strcat(a, ed->d_name), str));
				}
			}else{
				if(checkifsymlink(strcat(a, ed->d_name))){
					printf("%s\n", realpath(strcat(a, ed->d_name), str));
				}
			}
		}
	}else{
	}
}
