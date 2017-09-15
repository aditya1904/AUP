#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(int argc, char *argv[]){
	int pid, sleep_time, num_of_proc, i;
	sleep_time = atoi(argv[2]);
	num_of_proc = atoi(argv[1]);
	printf("Starting to create %d children now.\n", num_of_proc);
	for(i = 0; i < num_of_proc; i++){
		pid = fork();
		if (pid == 0){
			printf("sleeping ::::\n");
			sleep(sleep_time);
			exit(0);
		}
		else if(pid != -1){
			printf("pid ::::: %d \n", pid);
			waitpid(pid - 1, NULL, 0);
		}else{
			printf("Error in fork \n");
		}
	}
	wait(0);
	printf("All processes exited. \n");
}
