#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void err_sys(const char* x){
	perror(x);
	exit(1);
}

static void sig_quit(int signo){
	printf("caught SIGQUIT\n");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		err_sys("can’t reset SIGQUIT");
}

void check_sigset(sigset_t sigset){
	int i;
	for(i = 0; i < 31; i++){
		if(sigismember(&sigset, i)){
			printf("SIGNAL %d present\n", i);
		}
	}
}

int main(void){
	sigset_t newmask, oldmask, pendmask, sigset;
	pid_t pid;

	if (signal(SIGQUIT, sig_quit) == SIG_ERR)
		err_sys("can’t catch SIGQUIT");

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT); // adding SIGQUIT to newmask

	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) // added SIGQUIT to BLOCK
		err_sys("SIG_BLOCK error");

	printf("Send SIGQUIT signals\n");
	sleep(5);
	/* SIGQUIT here will remain pending */
	if((pid = fork()) == -1){
		err_sys("Fork Error");
	}

	if(pid){
		printf("IN PARENT:\n");
		if (sigprocmask(0, NULL, &sigset) < 0) {
			err_sys("Error getting signal mask");
		}
		else {
			check_sigset(sigset);
		}

		if (sigpending(&pendmask) < 0)
			err_sys("sigpending error");

		if (sigismember(&pendmask, SIGQUIT))
			printf("IN PARENT: SIGQUIT pending\n");

		wait();
	}
	else {
		sigset_t childsigset;
		printf("IN CHILD:\n");
		if (sigprocmask(0, NULL, &childsigset) < 0) {
			err_sys("Error getting signal mask");
		}
		else {
			check_sigset(childsigset);
		}

		if (sigpending(&pendmask) < 0){
			err_sys("sigpending error");
		}

		if (sigismember(&pendmask, SIGQUIT)){
			printf("IN CHILD: SIGQUIT pending\n");
		}
		else {
			printf("IN CHILD: SIGQUIT not pending in CHILD\n");
		}
	}
}
