#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<linux/limits.h>
int main(int argc, char *argv[]){
	struct stat statbuff;
	char filename[PATH_MAX] = "./";
	strcat(filename, argv[1]);
	if (stat(filename, &statbuff) == -1){
		perror("ERR:");
		exit(1);
	}

	printf("device number : %d\n", statbuff.st_dev);
	if((statbuff.st_mode & S_IFMT) == S_IFREG){
		printf("regular bole\n");
	}
}
