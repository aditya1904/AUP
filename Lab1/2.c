#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<fcntl.h>
int main(){
	int fd, fd2, size = 100, i;
	fd = open("./sample2", O_RDONLY);
	char *buff = (char *)malloc(size);
	for(i = 0; i < size; i++){
		buff[i] = '\0';
	}
	if(read(fd, buff, size-1) == -1){
		printf("Reading failed\n");
	}
	close(fd);
	fd = open("./sample2", O_TRUNC | O_WRONLY);
	if(write(fd, buff, size) == -1){
		printf("Writing failed\n");
	}
	close(fd);
}
