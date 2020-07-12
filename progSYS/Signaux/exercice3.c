#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

/*

Exercice 3 :
Ecrire un programme qui crée 5 fils. Chaque fils envoie la valeur de retour au processus père tel que :
Le processuss fils n◦ 1 renvoie la valeur 1
Le processuss fils n◦ 2 renvoie la valeur 4
Le processuss fils n◦ 3 renvoie la valeur 9
...
Le père doit également afficher les PID de ses fils.
Appels Systèmes : fork(), waitpid()

*/

int main(){
	int i, stat;
	int pid[5];

	for(i=1; i<=5; i++){
		if((pid[i]=fork()) == 0){
			sleep(1);
			exit(i*i);
		}
	}
	for(i=1; i<=5; i++){
		int cpid = waitpid(pid[i], &stat, 0);

		if(WIFEXITED(stat))
			printf("child %d terminated with status %d \n",cpid, WEXITSTATUS(stat));
		
	}

	return 0;
}