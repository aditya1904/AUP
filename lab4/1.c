#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[], char *envp[]){
	int i = 0;
	char buff[256];

	while(envp[i]){
		printf("%s\n", envp[i]);
		i += 1;
	}
	printf("Enter a env varible\n");
	scanf("%s", buff);
	if(putenv(buff) == -1){
		perror("putenv");
	}
	i = 0;
	while(envp[i]){
		printf("%s\n", envp[i]);
		i += 1;
	}
}
