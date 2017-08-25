#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>



int main(int argc, char *argv[]){
	mode_t old;
	old = umask(0);
	printf("%d\n", old);
	umask(old);
}
