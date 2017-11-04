#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<setjmp.h>

static jump_buf env;

int sig_alrm(int signo){
	longjmp(env, 1);
}

unsigned int mysleep(unsigned int secs){
	int time_left;
	time_left = alarm(0); /* checking if any previously set alarm function has some unslept seconds left */

	if(setjmp(env) == 0){
		alarm(secs - time_left); /* adding that time for user set value */
		pause();
	}
}

int main(){
	mysleep(1);
}

