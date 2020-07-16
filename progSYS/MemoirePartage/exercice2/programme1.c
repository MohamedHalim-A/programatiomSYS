#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>

/*
Exercice 2 :
Deux processus P1 et P2 sans liens parenté partagent un segment 
de mémoire de type entier. on
désire avoir l’affichage suivant à l’exécution:
P1 : 2 4 6 8 10
P2 : 13 16 19 22 25
Ecrire les deux programmes C sous Unix implémentant P1 et P2.
Appels Systèmes : shmget(), shmat(), shmctl(),shmdt().
*/

int main(int argc, char* argv[]){

	int* ptr;

	key_t key = ftok("Exo2file", 78);

	int shmid = shmget(key, sizeof(int), IPC_CREAT|0666);

	if(shmid == -1){
		perror("shmget");
		exit(0);
	}

	ptr = (int*)shmat(shmid, (void*)0, 0);

	(*ptr)=0;

	printf("programme1 : \t");
	do{
		(*ptr)=(*ptr)+2;
		printf("%d   ",(*ptr));
	}while((*ptr) % 5 != 0);

	printf("\n");

	shmdt(ptr);

	return 0;
}