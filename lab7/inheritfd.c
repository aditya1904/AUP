#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#define filerr(fd,msg) if((fd) < 0){perror((msg));return 0;}

int main(int argc, char *argv[], char *envp[]) {
    if (argc < 3) {
        printf("Usage: %s outfile infile\n", argv[0]);
        return 0;
    }

    int out = open(argv[1], O_RDWR | O_CREAT, 0777);
    int in = open(argv[2], O_RDONLY);

    char outmsg0[] = "[parent-written]";
    printf("Parent PID %d has written \"%s\" to %s\n", getpid(), outmsg0, argv[1]);
    write(out, outmsg0, sizeof (outmsg0));

    char inmsg[16];
    inmsg[1 + read(in, inmsg, 5)] = 0;
    printf("Parent PID %d) has read \"%s\" from %s\n", getpid(), inmsg, argv[2]);

    switch (fork()) {
        case -1:
            printf("Fork error");
            break;
        case 0:
            printf("Calling exec ls.sh");
            execl("ls.sh", "ls.sh", 0);
            break;
        default: wait(NULL);
    }
}
