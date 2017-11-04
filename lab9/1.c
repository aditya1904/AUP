#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void err_sys(const char* x){
	perror(x);
	exit(1);
}

void signal_handler(int SIGNAL){
	if(SIGNAL == SIGTERM){
		printf("Signal SIGTERM received.\n");
	}
	else {
		printf("received signal %d\n", SIGNAL);
	}
}

int main(){
	if(signal(SIGTERM, signal_handler) == SIG_ERR){
		err_sys("Can't catch SIGTERM");
	}
	if(signal(SIGINT, SIG_IGN) == SIG_ERR){
		err_sys("Can't catch SIGINT");
	}
	if(signal(SIGSEGV, SIG_DFL) == SIG_ERR){
		err_sys("Can't catch SIGSEGV");
	}
	sleep(50);
	pause();
}
