#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

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

void ls_l(char *dname){
	DIR *dir;
	struct dirent *ent;
	struct stat st;
	struct passwd *uinfo;
	struct group *ginfo;
	char fname[8], ftmp[8], pms[16], time[32];
	int ftype;
	time_t val;

	//stat(dname, &st);
	//printf("total %d\n", st.st_blocks);

	strcpy(fname, dname);
	strcat(fname, "/");

	dir = opendir(dname);
	if(!dir){
		printf("Error opening directory\n");
		return;
	}
	while((ent = readdir(dir)) != NULL){
		if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0){
			strcpy(ftmp, fname);
			strcat(ftmp, ent->d_name);
			stat(ftmp, &st);
			
			getPms(pms, st.st_mode);

			val = st.st_mtime;
			strftime(time, 32, "%b %d %H:%M", localtime(&val));

			uinfo = getpwuid(st.st_uid);
			ginfo = getgrgid(st.st_gid);

			printf("%s %s %s %u %s %s\n", pms, uinfo->pw_name, ginfo->gr_name, st.st_size, time, ent->d_name);
		}
	}

}

int main(){
	int r, n;
	struct stat st;
	mode_t mode;

	r = mkdir("junk", 0755);
	if(r == -1){
		printf("Error creating directory junk\n");
		return 0;
	}
	int i;
	char fname[8] = "junk/_";
	for(i = 1; i <= 5; i++){
		fname[5] = '0' + i;
		r = creat(fname, 0666);
		if(r == -1){
			printf("Error creating file junk/%d\n", i);
			return 0;
		}
		n = write(r, "hello", 5);
		close(r);
	}

	stat("junk", &st);

	ls_l("junk");										//ls -l junk
	printf("\n");

	mode = st.st_mode;
	mode = mode & ~(S_IRUSR | S_IRGRP | S_IROTH);
	r = chmod("junk", mode);							//chmod -r junk
	if(r == -1)
		printf("Permission denied\n");

	ls_l("junk");											//ls -l
	printf("\n");

	stat("junk", &st);
	mode = st.st_mode;
	mode = mode | (S_IRUSR | S_IRGRP | S_IROTH);
	r = chmod("junk", mode);							//chmod +r junk
	if(r == -1)
		printf("Permission denied\n");

	ls_l("junk");										//ls -l junk
	printf("\n");

	stat("junk", &st);
	mode = st.st_mode;
	mode = mode & ~(S_IXUSR | S_IXGRP | S_IXOTH);
	r = chmod("junk", mode);							//chmod -x junk
	if(r == -1)
		printf("Permission denied\n");

	r = chdir("junk");									//cd junk
	if(r == -1)
		printf("Permission denied\n");

	stat("junk", &st);
	mode = st.st_mode;
	mode = mode | (S_IXUSR | S_IXGRP | S_IXOTH);
	r = chmod("junk", mode);							//chmod +x junk
	if(r == -1)
		printf("Permission denied\n");

	r = chdir("junk");									//cd junk
	if(r == -1)
		printf("Permission denied\n");
	else{printf("cd into junk successs\n");}

}


/*
mkdir junk
for i in 1 2 3 4 5
do
	echo hello > junk/$i
done

ls -l junk
chmod -r junk
ls -l
chmod +r junk
ls -l junk
chmod -x junk
cd junk
chmod +x junk
cd junk*/
