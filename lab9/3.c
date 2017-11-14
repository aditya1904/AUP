#include<setjmp.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

static jmp_buf env;

int abs(int x){
	if ( x > 0){
		return x;
	}else{
		return -1 * x;
	}
}

int sig_alrm(int signo){
	longjmp(env, 1);
}

unsigned int mysleep(unsigned int secs){
	int time_left;
	time_left = alarm(0); /* checking if any previously set alarm function has some unslept seconds left */
	void *func = signal(SIGALRM, sig_alrm);
	printf("remaining time is %d\n", time_left);
	if(time_left > secs){
		if(setjmp(env) == 0){
			alarm(secs); /* adding that time for user set value */
			pause();
		}
		alarm(time_left - secs);
	}else{
		alarm(time_left);
		pause();
		if(setjmp(env) == 0){
			alarm((secs - time_left));  /* adding that time for user set value */
		}
	}
	signal(SIGALRM, func); 
}

int main(){
	alarm(9);
//a	mysleep(4);
}

