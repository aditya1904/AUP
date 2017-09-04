#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
static void f1(int, int, int, int); 
static void f2(void);
static jmp_buf jmpbuffer;
static int globval; //Global Variable
int main() {
	int autoval; //Automatic Variable
	register int regival; //Register Variable 
	int volatile volaval; //Volatile Variable
	static int statval; //Static Variable
	globval = 1; autoval = 2; regival = 3; volaval = 4; statval = 5;
	/* The value of all types of variables are set before setjmp. When compiled using optimization (-O),
	   AUTOMATIC and REGISTER variables get stored in the register. Rest get stored in memory. When 
	   compiled without optimization, all go to memory. */
	if(setjmp(jmpbuffer) != 0) {
		printf("after longjmp:\n");
		printf("globval = %d, autoval = %d, regival = %d, volaval = %d, statval = %d\n", globval, autoval, regival, volaval, statval);
		exit(0);
	}
	globval = 95, autoval = 96, regival = 97, volaval = 98, statval = 99;
	f1(autoval, regival, volaval, statval);
	exit(0);
}

static void f1(int i, int j, int k, int l) {
	printf("in f1(): \n");
	printf("globval = %d, autoval = %d, regival = %d, volaval = %d, statval = %d\n", globval, i, j, k, l);
	/* In the above printf, the values of variables will be the same as passed to the function f1 as longjmp hasnt been invoked yet */
	f2();
}

static void f2(void) {
	longjmp(jmpbuffer, 1);
	/* While invoking this longjmp, the variables that are stored in memory will have values as of the time of longjmp, while variables 	       stored in registers are restored to their values when setjmp was called.
	   Therefore values of autoval and regival get changed to 2 and 3 respectively whereas the rest remain the same */ 
}
	 
