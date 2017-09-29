#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>

void* hello(void *cpu_id){
	int cpu = *(int *)cpu_id;
	pthread_t thread = pthread_self();
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);
	
	int s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
	if (s != 0)
		printf("Error for CPU %d\n", cpu);
}

int main(){
	long int n_cpu =  sysconf(_SC_NPROCESSORS_ONLN);
	int j;
	pthread_t threads[n_cpu];
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	for (j = 0; j < n_cpu; j++){
		CPU_SET(j, &cpuset);
	}
	for (j = 0; j < n_cpu; j++){
		pthread_create(&threads[j], NULL, hello, &j);
	}
	printf("Set returned by pthread_getaffinity_np() contained:\n");
	for (j = 0; j < CPU_SETSIZE; j++){
		if (CPU_ISSET(j, &cpuset))
			printf("    CPU %d\n", j);
	}
	exit(EXIT_SUCCESS);	
}
