#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    if (argc < 2) {
        printf("Usage: %s <file to display>\n", argv[0]);
        uid_t uid = getuid();
        uid_t euid = geteuid();
        gid_t gid = getgid();
        gid_t egid = getegid();
        printf("UID:%d EUID:%d GID:%d EGID:%d\n", uid, euid, gid, egid);
        return 0;
    }
    execvp("/bin/cat",  argv);
}