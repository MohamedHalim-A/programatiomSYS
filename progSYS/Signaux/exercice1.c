#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

/*

Exercice 1 : Synchronisation Père/Fils ( Dernier exercice de la Série 2)
Ecrire le programme C sous Unix qui permet à un processus père de créer un processus Fils. Le père et
le Fils doivent s’exécuter en parallèle et permettent l’affichage suivant :
Fils: 2 4 6 8 10
Père: 3 6 9 12 15
Fils: 12 14 16 18 20
Père: 18 21 24 27 30
........
Fils : ........
Père: ..............99
Appels Systèmes : fork(), signal(), kill(), pause()

*/

void handler(int sig){
	printf("\n");
}

int main(){

	int pid, i=0;
	signal(SIGINT,handler);
	pid = fork();

	while(i<99){

		if(pid == -1){

			perror("fork");
			exit(0);

		}else if(pid == 0){

			printf("Fils : ");

			do{
				i=i+2;
				printf("%d \t",i );
			}while (i%5 != 0);

			kill(getppid(),SIGINT);
			pause();

		}else{
			sleep(1);
			printf("pere : ");

			do{
				i=i+3;
				printf("%d \t",i );
			}while(i%5 != 0 && i<99);

			kill(pid, SIGINT);
			pause();
		}
	}
	return 0;
}