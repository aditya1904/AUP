#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include<stdlib.h>

void ls (char *pathname) {
        struct stat sb = {0};
        int s = stat(pathname, &sb);
        printf("I-node number:            %ld\n", (long) sb.st_ino);
        printf("Mode:                     %lo (octal)\n",(unsigned long) sb.st_mode);
        printf("Link count:               %ld\n", (long) sb.st_nlink);
        printf("Ownership:                UID=%ld   GID=%ld\n",                  (long) sb.st_uid, (long) sb.st_gid);
        printf("Preferred I/O block size: %ld bytes\n", (long) sb.st_blksize);
        printf("File size:                %lld bytes\n",(long long) sb.st_size);
        printf("Blocks allocated:         %lld\n", (long long) sb.st_blocks);
        printf("==================================================================\n");

}
	
int main() {
	mkdir("junk", 0775);
	int i;
	FILE *fp;
	char *dest1 = "./junk/";
	char temp[20];
	char dest2[20];
	for(i = 1; i <= 5; i++) {
		sprintf(dest2, "%d", i);
		strcpy(temp, dest1);
		strcat(temp, dest2);
		fp = fopen(temp, "w+");
		fwrite("hello" , 1 , 5 , fp );
		fclose(fp);
	}
	ls("./junk");
	char mode[100];
        strcpy(mode, "0331");
        char buf[100] = "junk";
        
        i = strtol(mode, 0, 8);
        chmod (buf,i);
        ls("./");


        strcpy(mode , "0775");
        i = strtol(mode, 0, 8);
        chmod(buf,i);
        ls("./junk");


        strcpy(mode , "0664");
        i = strtol(mode, 0, 8);
        chmod(buf,i);
        ls("./junk");


        strcpy(mode , "0775");
        i = strtol(mode, 0, 8);
        chmod(buf,i);
        ls("./junk");
	
				
		
		
	return 0;


}
