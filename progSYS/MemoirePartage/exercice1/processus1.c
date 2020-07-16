#include <stdio.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/shm.h>

/*

Exercice 1 : Création Mémoires Partagées
Deux processus P1 et P2 sans liens parenté partagent un segment
 de mémoire permettant de stocker
des réel. le processus P1 crée la Mémoires Partagée et l’initialise 
avec la valeur passée en paramètre. le
deuxième processus accède au segment récupère la valeur calcule son 
carrée et affiche le résultat. Ecrire
les deux programmes C sous Unix implémentant P1 et P2.
Appels Systèmes : shmget(), shmat(), shmctl(),shmdt()

*/


int main(int argc, char* argv[]){

	float* ptr;

	//ftok pour generer un cle aleatoire
	key_t key = ftok("Process1File", 65);

	//shmget retour l'identifiant de la zonne memoire
	int shmid = shmget(key, sizeof(float), IPC_CREAT|0666);

	if(shmid == -1){
		perror("shmget");
		exit(0);
	}

	//shmat pour attacher une memoire partage
	ptr = (float*)shmat(shmid, (void*)0, 0);

	*ptr = atol(argv[1]);

	printf("La donne ecrite dans la memoire: %f \n", *ptr);

	// se dtacher de la memoire
	shmdt(ptr);

	return 0;
}