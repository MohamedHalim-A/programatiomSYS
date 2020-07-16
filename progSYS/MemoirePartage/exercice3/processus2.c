#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

#define key 100

typedef struct MemPartagee{
	int pid1; //pid du processus1
	int pid2; //pid du processus2
	int n; //numeros servant d'affichage
}MP;

void handler(){}

int main(){

	MP* mp;

	signal(SIGUSR1, handler);

	int shmid = shmget(key, sizeof(MP), IPC_EXCL);

	if(shmid == -1){
		perror("shmget");
		exit(0);
	}

	mp = (MP*) shmat(shmid, (void*)0, 0);

	mp->pid2 = getpid();

	while(mp->n < 100){
		printf("processus2:\t");
		do{
			mp->n += 3;
			printf("%d  ", mp->n);
		}while(mp->n % 5 != 0);

		printf("\n");

		kill(mp->pid1, SIGUSR1);
		pause();
	}
	shmdt(mp);
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}