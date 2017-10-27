#include<stdio.h>
#include<unistd.h>

int main(){
	if( acct("./a") < 0){
		perror("err");		
	}
}
