#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

typedef struct K{
	char *pattern;
	char *filename;
	pthread_mutex_t mutex;
	pthread_cond_t done;
}K;

void *search(void *k){
	K *p = (K *)k;
	pthread_mutex_lock(&p->mutex);
	char *name = p->filename, *pattern = p->pattern;
	pthread_mutex_unlock(&p->mutex);
	pthread_cond_signal(&p->done);
	char str[50];
	sprintf(str, "grep %s %s > /dev/null", pattern, name);
	if(!system(str)){
		printf("file %s has it. \n", name);
	}
	return NULL;
}

int main(int argc, char *argv[]){
	pthread_t th[3];
	int i;
	struct K k;
	pthread_mutex_init(&k.mutex, NULL);
	pthread_cond_init(&k.done, NULL);

	for(i = 0; i < argc - 2; i++){
		k.pattern = argv[1];
		k.filename = argv[i + 2];
		// printf("%s %s\n", k.pattern, k.filename);
		pthread_create(&th[i], NULL, search, &k);
		pthread_cond_wait(&k.done, &k.mutex);
	}

	for(i = 0; i < argc - 2; i++){
		pthread_join(th[i], NULL);
	}
}
