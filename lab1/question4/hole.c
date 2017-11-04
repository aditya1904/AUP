#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void invokeod(char * filename){
    printf(" > od -c %s\n", filename);
    char command[16];
    snprintf(command, sizeof(command), "od -c %s", filename);
    system(command);
}

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage : %s <filename>\n", argv[0]);
        exit(0);
    }
    char *filename = argv[1];
    char firstbuff[] = "aupassignt", secbuff[] = "aunxprolab", copyfile[] = "copyfile";
    int fd1, fd2, n;
    fd1 = open(filename , O_CREAT | O_WRONLY | O_TRUNC);
    if(fd1 == -1){
        perror("Error ");
        exit(1);
    }
    printf("Writing to file \"%s\"...\n", filename);
    // write any 10 bytes at an offset of 10 //
    lseek(fd1, 10, SEEK_SET);
    write(fd1, firstbuff, 10);
    // another 10 bytes at an offset of 30 //
    lseek(fd1, 30, SEEK_SET);
    write(fd1, secbuff, 10);
    close(fd1);
    // view the contents //
    invokeod(filename);

    // copy the contents of the file to another file without writing the bytes of 0 //
    printf("Copying to file \"%s\" without bytes of 0...\n", copyfile);
    char *buf;
    fd1 = open(filename , O_CREAT | O_RDONLY );
    if(fd1 == -1){
        perror("Error ");
        exit(1);
    }
    fd2 = open(copyfile , O_CREAT | O_WRONLY | O_TRUNC);
    if(fd2 == -1){
        perror("Error ");
        exit(1);
    }
    char ch;
    while((n = read(fd1, &ch, 1)) > 0){
        if(ch != '\0'){
            write(fd2, &ch, 1);
        }
    }
    close(fd1);
    close(fd2);

    // view the contents //
    invokeod(copyfile);
}
