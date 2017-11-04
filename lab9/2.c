#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void err_sys(const char* x){
	perror(x);
	exit(1);
}

void signal_handler(int SIGNAL){
	if(SIGNAL == SIGINT){
		printf("Signal SIGINT received in Parent.\n");
	}
	else {
		printf("received signal %d\n", SIGNAL);
	}
}

int main(){
	pid_t pid;
	if((pid = fork()) == -1){
		err_sys("Fork Error");
	}
	if(pid){
		if(signal(SIGINT, signal_handler) == SIG_ERR){
			err_sys("Can't catch SIGINT");
		}
		int time_remained = sleep(5);
		printf("Parent exiting with %d seconds left\n", time_remained);
	}
	else {
		pid_t parent_pid = getppid();
		if(kill(parent_pid, SIGINT) == -1){
			err_sys("Error sending Signal");
			exit(1);
		}
	}
	exit(0);
}