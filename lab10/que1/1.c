#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	pid_t pid1, pid2, pid;
	int p1[2], p2[2], p3[2], p4[2];
	char buf1[16], buf2[16], buf3[16], buf4[16];
	char cities[4][16] = {"Mumbai", "Delhi", "Cochin", "Chennai"};
	if(pipe(p1) == -1 || pipe(p2) == -1 || pipe(p3) == -1 || pipe(p4) == -1){
		perror("Pipe Error");
		exit(1);
	}

	if((pid1 = fork()) < 0){  // Forking Child 1
		perror("Failed to fork process \n");
		exit(1);
	}
	else if ( pid1 > 0 ){
		// Parent Here //
		close(p1[0]);	// Writing in Pipe 1
		write(p1[1], cities[0], 16); //Writing "Mumbai" on Pipe 1
		close(p1[1]);

		close(p2[1]); // Reading in Pipe 2
		if(read(p2[0], buf3, 16) == -1){
			perror("Pipe 2, Parent: Error:");
		} else {
			printf("In Parent: Pipe 2 Read: %s\n", buf3);
		}
		close(p2[0]);
		// FORKING CHILD 2 //
		if((pid2 = fork()) < 0){
			perror("Failed to fork process \n");
			exit(1);
		} else if (pid2 == 0) {
			//  CHILD 2 //
			close(p3[1]);
			if(read(p3[0], buf2, 16) == -1){
				perror("Pipe 3, Child 2: Error:");
			} else {
				printf("In Child 2: Pipe 3 Read: %s\n", buf2);
			}
			close(p3[0]);

			close(p4[0]);
			write(p4[1], cities[2], 16);  //Writing "Cochin" on Pipe 4
			close(p4[1]);
			// CHILD 2 DONE //
		} else {
			// PARENT HERE //
			close(p4[1]); // Reading in Pipe 4
			if(read(p4[0], buf4, 16) == -1){
				perror("Pipe 4, PArent: Error:");
			} else {
				printf("In Parent: Pipe 4 Read: %s\n", buf4);
			}
			close(p4[0]);
		}
	}
	else { // CHILD 1 (C1) //
		close(p1[1]);
		if(read(p1[0], buf1, 16) == -1){
			perror("Pipe 1, Child 1: Error:");
		} else {
			printf("In Child 1: Pipe 1 Read: %s\n", buf1);
		}
		close(p1[0]);

		close(p2[0]);
		write(p2[1], cities[1], 16); // Writing "Delhi" on Pipe 2
		close(p2[1]);

		close(p3[0]);
		write(p3[1], cities[3], 16); // Writing "Chennai" on Pipe 3
		close(p3[1]);
	}
}