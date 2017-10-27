#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	pid_t pid1, pid2, pid;
	int status;
	printf("Forking child 1 \n");
	if((pid1 = fork()) < 0){
		perror("Failed to fork process \n");
		exit(1);
	}
	if(pid1 == 0){
		sleep(3);
		printf("Exiting child 1 \n");
		exit(0);
	} else {
		printf("CHILD PID: %d, PPID: %d, PGID:%d \n", pid1, getpid(), getpgid(pid1));
		if(setpgid(pid1, pid1) == -1){
			perror("Setpgid failed");
		} else {
			printf("Setpgid success \n");
		}
		printf("CHILD PID: %d, PPID: %d, PGID:%d \n", pid1, getpid(), getpgid(pid1));
	}

	printf("Forking child 2 \n");
	if((pid2 = fork()) < 0){
		perror("Failed to fork process \n");
		exit(1);
	}
	if(pid2 == 0){
		execl("./some", "some", NULL);
	} else {
		pid = wait(&status);
		printf("CHILD PID: %d, PPID: %d, PGID:%d \n", pid2, getpid(), getpgid(pid2));
		if(setpgid(pid2, pid2) == -1){
			perror("Setpgid failed");
		} else {
			printf("Setpgid success \n");
		}
		printf("CHILD PID: %d, PPID: %d, PGID:%d \n", pid2, getpid(), getpgid(pid2));
	}
}