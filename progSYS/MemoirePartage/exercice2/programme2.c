#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char* argv[]){

	int* ptr;

	key_t key = ftok("Exo2file", 78);

	int shmid = shmget(key, sizeof(int), IPC_CREAT|0666);

	if(shmid == -1){
		perror("shmget");
		exit(0);
	}

	ptr = (int*)shmat(shmid, (void*)0, 0);

	printf("Programme2 : \t");

	do{
		(*ptr) = (*ptr)+3;
		printf("%d   ", (*ptr));
	}while((*ptr) % 5 != 0);

	printf("\n");

	shmdt(ptr);

	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}