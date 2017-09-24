#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Usage : %s <filename>\n", argv[0]);
		exit(0);
	}
	char *filename = argv[1];
	char buffer1[] = "abcde", buffer2[] = "12345";
	int n, fd1;

	int pid = fork();
	if(pid){
		fd1 = open(filename , O_CREAT | O_WRONLY | O_TRUNC);
		if(fd1 == -1){
			perror("Error ");
			exit(1);
		}
		printf("Writing \"%s\" to file \"%s\" in parent process...\n", buffer1, filename);
		write(fd1, buffer1, strlen(buffer1));
		wait(NULL);
	}
	else {
		sleep(2);
		printf("Trying to write \"%s\" to file \"%s\" in child process...\n", buffer2, filename);
		write(fd1, buffer2, strlen(buffer2));
	}
	close(fd1);

	return 0;
}
