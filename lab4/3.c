#include<stdio.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>


int main(){
	pid_t pid;
	/* start time*/
	pid = getpid();
	/* end time */
	/* start time */
	int x = fork();
	if(x != 0){
	/* end time*/
	}
}
