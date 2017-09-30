#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 5

struct params {
	pthread_mutex_t mutex;
	pthread_cond_t done;
	int id;
};
typedef struct params params_t;

void* hello(void* arg){
	int id;
	pthread_mutex_lock(&(*(params_t*)(arg)).mutex);
	id = (*(params_t*)(arg)).id;
	printf("Thread id-> %d\n", id);
	pthread_mutex_unlock(&(*(params_t*)(arg)).mutex);
	pthread_cond_signal (&(*(params_t*)(arg)).done);
}

int main() {
	pthread_t threads[10];
	params_t params;
	pthread_mutex_init (&params.mutex , NULL);
	pthread_cond_init (&params.done, NULL);

	int i;
	for(i = 0; i < N; i++) {
		params.id = i;
		pthread_create(&threads[i], NULL, hello, &params);
		pthread_cond_wait (&params.done, &params.mutex);
	}

	for(i = 0; i < N; i++) {
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy (&params.mutex);
	pthread_cond_destroy (&params.done);

	return 0;
}
