#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

void* hello(void *cpu_set){
	pthread_t thread = pthread_self();
	cpu_set_t *cpuset = (cpu_set_t *)cpu_set;
	int s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), cpuset);
	if (s != 0)
		printf("Error for CPU");
}

int main(){
	long int n_cpu =  sysconf(_SC_NPROCESSORS_ONLN);
	printf("No. of CPUs -> %ld\n", n_cpu);
	int j, s;
	pthread_t threads[n_cpu];
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	for (j = 0; j < n_cpu; j++){
		CPU_SET(j, &cpuset);
	}
	printf("Attaching a thread to a CPU...\n");
	for (j = 0; j < n_cpu; j++){
		pthread_create(&threads[j], NULL, hello, &cpuset);
	}

	printf("Checking for threads, if attached to a CPU...\n");
	for (j = 0; j < n_cpu; j++){
		s = pthread_getaffinity_np(threads[j], sizeof(cpu_set_t), &cpuset);
		printf("Thread %d -> %s\n", j, !s?"true":"false");
	}

	for(j = 0; j < n_cpu; j++) {
		pthread_join(threads[j], NULL);
	}
	exit(EXIT_SUCCESS);
}
