#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void invokecat(char * filename){
    printf(" > cat %s\n", filename);
    char command[16];
    snprintf(command, sizeof(command), "cat %s", filename);
    system(command);
    printf("\n");
}

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage : %s <filename>\n", argv[0]);
        exit(0);
    }
    char *filename = argv[1];
    char buffer1[] = "abcde", buffer2[] = "12345";
    int fd1, fd2, n;
    fd1 = open(filename , O_CREAT | O_WRONLY | O_TRUNC);
    if(fd1 == -1){
        perror("Error ");
        exit(1);
    }
    printf("Writing \"%s\" to file \"%s\"...\n", buffer1, filename);
    write(fd1, buffer1, strlen(buffer1));
    close(fd1);

    invokecat(filename);

    fd1 = open(filename, O_WRONLY | O_APPEND);
    if(fd1 == -1){
        perror("Error ");
        exit(1);
    }
    printf("Writing \"%s\" to file \"%s\"...\n", buffer2, filename);
	int x;
	x = lseek(fd1, 0, SEEK_SET);
	printf("Offset after lseek -> %d \n",x);
    write(fd1, buffer2, strlen(buffer2));
    close(fd1);

    invokecat(filename);

}
