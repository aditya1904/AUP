#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
	int fd;
	fd = open("./sample2", O_RDWR);
	if (fd == -1){
		printf("Cannot open sample2\n");
	}
	char *buff = (char *)malloc(10);
	if(read(fd, buff, 10) == -1){
		printf("Failiure in reading\n");
	}
	if(fcntl(fd, F_SETFL, O_APPEND) == -1){
		printf("Some error\n");
	}

	if(write(fd, "hello", sizeof("hello"))){
		printf("Writing failed");
	}
	close(fd);
	
}
