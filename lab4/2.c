#include<stdio.h>
#include<setjmp.h>

static jmp_buf jmpbuffer;

void hello(){
	longjmp(jmpbuffer, 1);
}

int main(){
	register int i = 100;
	int auto_var = 101;
	volatile int vol = 102;

	if(setjmp(jmpbuffer) != 0){
		printf("After long jump:\n");
		printf("%d %d %d\n", i, auto_var, vol);
		exit(0);
	}

	i = 1; auto_var = 2; vol = 3;
	printf("In main. Without long jumps : %d %d %d\n", i, auto_var, vol);
	hello();
	exit(0);
}


