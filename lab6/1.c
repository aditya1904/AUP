#include<stdio.h>
#include<pthreads.h>

int search_pattern(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
  
    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++)
    {
        int j;
  
        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++)
            if (txt[i+j] != pat[j])
                break;
 
        if (j == M)  // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
    		return 1;
    }
    return 0;
    
}

void search(char *name, char *pattern){
	int fd = open(name);
	char line[100];
	while(read(fd, line, 100)){
		if(search_pattern(line, pattern)){
			printf("Found in %s\n", name);
		}
	}			
}

int main(){
	pthread_t th[3];
	int i;
	for(i = 0; i < 3; i++){
		pthread_create(&th[i], NULL, search, argv[1], argv[i + 2]);
	}	

	for(i = 0; i < 3; i++){
		pthread_join(th[i]);	
	}
}
