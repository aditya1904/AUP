#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<fcntl.h>
int main(int argc, char *argv[]){
	int fd, fd2, size, i, res;
	if(argc != 3){
		printf("Not enough arguments.\n./a.out <filename> <size>\n");
		exit(0);
	}

	fd = open(argv[1], O_RDONLY);
	if(fd == -1){
		perror("Cannot open");
		exit(1);
	}

	size = atoi(argv[2]);
	char *buff = (char *)malloc(size);

	for(i = 0; i < size; i++){
		buff[i] = '\0';
	}

	res = read(fd, buff, size - 1);

	if(res  == -1){
		printf("Failiure in reading\nHave you entered the offset correctly?\n");
		exit(0);
	}else if(res < size - 1){
		printf("file is less than %d characters\n", size - 1);
	}

	close(fd);

	fd = open(argv[1], O_TRUNC | O_WRONLY);
	if(write(fd, buff, size) == -1){
		printf("Writing failed\n");
	}
	close(fd);
}
