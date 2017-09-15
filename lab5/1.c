#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
//	pid_t ruid, euid, rguid, eguid, ppid, pid;
	if(fork() != 0){
		printf("IN PARENT\nruid: %d euid: %d rgid: %d egid: %d pid: %d ppid: %d\n", getuid(), geteuid(), getgid(), getegid(), getpid(), getppid());
	}else{
		printf("IN CHILD\nruid: %d euid: %d rguid: %d eguid: %d pid: %d ppid: %d\n", getuid(), geteuid(), getgid(), getegid(), getpid(), getppid());
	}
}
