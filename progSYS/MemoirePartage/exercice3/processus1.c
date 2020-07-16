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

//une fonction handler pour redefinir le comportement du signal

void handler(){}

int main(){

	MP* mp;

	signal(SIGUSR1, handler);

	int shmid = shmget(key, sizeof(MP), IPC_CREAT|0666);

	if(shmid == -1){
		perror("shmget");
		exit(0);
	}

	mp = (MP*) shmat(shmid, (void*)0, 0);

	mp->pid1 = getpid(); //pid de processus1

	mp->n = 0;

	while(mp->n < 100){
		printf("processus1:\t");
		do{
			mp->n += 2;
			printf("%d  ", mp->n);
		}while(mp->n %5 != 0);
		printf("\n");

		kill(mp->pid2, SIGUSR1);
		pause();
	}
	shmdt(mp);

	return 0;
}