#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	pid_t pid1, pid2, pid;
	int status;
	if((pid1 = fork()) < 0){
		perror("Failed to fork process...\n");
		exit(1);
	}
	if(pid1 == 0){
		printf("In child process...\n");
		printf("Before setsid...\n");
		printf("Session id: %d, pid: %d, ppid: %d ...\n", getsid(), getpid(), getppid());
		if((pid2 = setsid()) < 0){
			printf("Failed to setsid...\n");
			exit(1);
		} else {
			printf("After setsid...\n");
			printf("Session id: %d, pid: %d, ppid: %d ...\n", pid2, getpid(), getppid());
		}
		if(open("/dev/tty", O_RDONLY) == -1){
			printf("The process does not have a controlling terminal...\n");
		} else {
			printf("It has a controlling terminal\n");
		}
	} else {
		pid = wait(&status);
	}
	exit(0);
}