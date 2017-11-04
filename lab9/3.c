#include<setjmp.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

static jmp_buf env;

int sig_alrm(int signo){
	longjmp(env, 1);
}

unsigned int mysleep(unsigned int secs){
	int time_left;
	time_left = alarm(0); /* checking if any previously set alarm function has some unslept seconds left */
	printf("remaining time is %d\n", time_left);
	if(setjmp(env) == 0){
		alarm(secs - time_left); /* adding that time for user set value */
		pause();
	}
}

int main(){
	alarm(3);
	mysleep(4);
}

