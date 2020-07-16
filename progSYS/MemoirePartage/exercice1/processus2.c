#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main(int argc, char* argv[]){

	float* ptr;

	key_t key = ftok("Process1File", 65);

	int shmid = shmget(key, sizeof(float), IPC_CREAT|0666);

	if(shmid == -1){
		perror("shmid");
		exit(0);
	}

	ptr = (float*)shmat(shmid, (void*)0, 0);
	*ptr = (*ptr)*(*ptr);

	printf("Le carre du donne recuperer de la memoire :%f\n", (*ptr));

	shmdt(ptr);

	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}