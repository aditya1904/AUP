#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	int fd, res;

	if(argc != 2){
		printf("Not enough arguments.\n./a.out <filename>\n");
		exit(0);
	}

	fd = open(argv[1], O_RDWR | O_APPEND);
	if (fd == -1){
		perror("Cannot open");
		exit(1);
	}
	char *buff = (char *)malloc(10);
	res = read(fd, buff, 10);

	if(res == -1){
		perror("Failiure in reading\n");
		exit(1);
	}else if(res < 10){
		perror("file is less than 10 characters.\n");
	}

/*	if(fcntl(fd, F_SETFL, O_APPEND) == -1){
		perror("Some error\n");
	}*/
	if(write(fd, "hello", sizeof("hello")) == -1){
		perror("Writing failed\n");
	}
	close(fd);

}
