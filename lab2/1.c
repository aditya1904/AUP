#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>

void getPms(char *pms, mode_t mode){

	pms[0] = S_ISDIR(mode) ? 'd' : '-';
	pms[1] = (mode & S_IRUSR) ? 'r' : '-';
	pms[2] = (mode & S_IWUSR) ? 'w' : '-';
	pms[3] = (mode & S_IXUSR) ? 'x' : '-';
	pms[4] = (mode & S_IRGRP) ? 'r' : '-';
	pms[5] = (mode & S_IWGRP) ? 'w' : '-';
	pms[6] = (mode & S_IXGRP) ? 'x' : '-';
	pms[7] = (mode & S_IROTH) ? 'r' : '-';
	pms[8] = (mode & S_IWOTH) ? 'w' : '-';
	pms[9] = (mode & S_IXOTH) ? 'x' : '-';
	pms[10] = '\0';
	
}

int main(){
	DIR *dr;
	struct dirent *ent;
	struct stat statbuff, st;
	struct passwd *uin;
	struct group *gin;
	char fname[] = "./junk/0", perm[16];
	int junk, n, fd;
	int mode;

	junk = mkdir("junk", 0755);
	if(junk == -1){
		perror("Error!");
		exit(1);
	}

	int i;
	for(i = 0; i < 5; i++){
		fname[7] = '0' + i;
		fd = open(fname,O_CREAT | O_TRUNC | O_WRONLY ,0766);
		write(fd, "hello", sizeof("hello"));
		close(fd);
	}
	dr = opendir("./junk");

	while((ent = readdir(dr)) != NULL){
		printf("%s\n", ent -> d_name);
		char f[] = "./junk/";
		strcat(f, ent -> d_name);
		printf("%s\n", f);
		stat(f, &statbuff);
		getPms(perm,statbuff.st_mode);

		uin = getpwuid(statbuff.st_uid);
		gin = getgrgid(statbuff.st_gid);

		printf("%s %s %s %u %s %s\n", perm, uin->pw_name, gin->gr_name, statbuff.st_size,  ent->d_name);
	}

// ls -l
	dr = opendir(".");

        while((ent = readdir(dr)) != NULL){
                printf("%s\n", ent -> d_name);
                char f[] = "./";
                strcat(f, ent -> d_name);
                printf("%s\n", f);
                stat(f, &statbuff);
                getPms(perm,statbuff.st_mode);

                uin = getpwuid(statbuff.st_uid);
                gin = getgrgid(statbuff.st_gid);

                printf("%s %s %s %u %s %s\n", perm, uin->pw_name, gin->gr_name, statbuff.st_size,  ent->d_name);
        }

	stat("junk", &statbuff);
	mode = statbuff.st_mode;
	mode = mode | (S_IRUSR | S_IRGRP | S_IROTH);
	dr = chmod("junk", mode);							
	if(dr == -1)
		printf("Permission denied\n");

	printf("\n");

	stat("junk", &statbuff);
	mode = statbuff.st_mode;
	mode = mode & ~(S_IXUSR | S_IXGRP | S_IXOTH);
	dr = chmod("junk", mode);							
	if(dr == -1)
		printf("Permission denied\n");

	dr = chdir("junk");	
	if(dr == -1)
		printf("Permission denied\n");

	stat("junk", &st);
	mode = st.st_mode;
	mode = mode | (S_IXUSR | S_IXGRP | S_IXOTH);
	dr = chmod("junk", mode);							
	if(dr == -1)
		printf("Permission denied\n");

	dr = chdir("junk");								
	if(dr == -1)
		printf("Permission denied\n");
}

