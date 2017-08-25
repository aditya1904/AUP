#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc, char *argv[]){
	int fd1, fd2, a,b;
	char str[100];
	fd1 = open("./in1", O_RDONLY);
	fd2 = open("./ou2", O_WRONLY);
	dup2(fd2, 1);
	dup2(fd1, 0);
	scanf("%d%d", &a, &b);
	printf("%d", a+b);
	close(fd1);
	close(fd2);		
}
