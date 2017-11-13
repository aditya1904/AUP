#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/sem.h>
int main()
{
	key_t key = 5678, skey = IPC_PRIVATE;
	int i;	
	int shmid = shmget(key,10 , IPC_CREAT | 0666), semid = semget(skey, 1, IPC_CREAT | IPC_EXCL | 0666);
	char *shm = shmat(shmid, NULL, 0), *ptr;
	struct sembuf sb;
	ptr = shm;
	if(semid >= 0){

		union semun{
			int val;
			struct semid_dss *buf;
			short *array;
		}arg;

		arg.val = 1;
		semctl(semid, 0, SETVAL, arg); 
		i = 0;
		while(1){
			if(i == 9){
				i = 0;
				ptr = shm;
			}

			sb.sem_num = 0;
			sb.sem_op = -1;			
			semop(semid, &sb, 1);
			if(*ptr == 'c'){
				// buffer is empty.
				printf("Buffer is empty\n");
				sb.sem_num = 0;
				sb.sem_op = 1;			
				semop(semid, &sb, 1);
				continue;
			}else{
				// get the semaphore
				printf("Consuming\n");
				*ptr = 'c';
				ptr++;
				i = (i + 1) % 10;
				// release the semaphore
			}
			
			sb.sem_num = 0;
			sb.sem_op = 1;			
			semop(semid, &sb, 1);
			
		}
	
	}
	shm[10] = NULL;
	exit(0);
}
