#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    if (argc < 3) {
        printf("Input as %s read-from write-to\n", argv[0]);
        return 0;
    }

    close(STDIN_FILENO);
    if (open(argv[1], O_RDONLY) < 0) {
        perror("Could not open input file");
        return -1;
    }
    close(STDOUT_FILENO);
    if (open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644) < 0) {
        perror("Could not open output file");
        return -1;
    }
    execl("/bin/cat", "cat", NULL);
}
