#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>
#define filerr(fd,msg) if((fd) < 0){perror((msg));return 0;}

int main(int argc, char *argv[], char *envp[]) {
    if (argc < 2) {
        printf("put input as : %s <file containing command name>\n", argv[0]);
        return 0;
    }
    int fd = open(argv[1], O_RDONLY);
    filerr(fd, "could not open file");
    __off_t end = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    char cmdname[end + 2];
    cmdname[1 + read(fd, cmdname + 1, end)] = 0;
    char *c = cmdname + 1;
    while (*c) {
        if (isspace(*c)) {
            *c = 0;
            break;
        }
        c++;
    }

    close(fd);
    if (fork() == 0) {
        printf("Starting \"%s\"\n", cmdname + 1);
        int execret = execlp(cmdname + 1, cmdname + 1, NULL);
        //if error
        printf("Exec returned %d", execret);
    }
    wait(0);
}
