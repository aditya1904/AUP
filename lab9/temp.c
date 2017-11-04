#include<stdio.h>
#include<unistd.h>
#include<signal.h>
int sig_alrm(int x){
	printf("HI\n");
	exit(0);
}

int main(){
	int i = 0;
	signal(SIGALRM, sig_alrm);
	alarm(2);
	while(1);
}
