#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
int main(int argc, char *argv[]){
	struct stat statbuff;
	if(stat(argv[1], &statbuff) == -1){
		perror("Err:");	
	}
}
