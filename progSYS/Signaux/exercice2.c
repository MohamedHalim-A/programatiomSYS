#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Exrcice2
Quel est la valeur du compteur count ?
Rappel :
Lorsque l’appel système wait() est appelée, l’exécution du père est suspendue jusqu’à ce qu’un fils se
termine. De plus, il faut mettre autant d’appels de wait() qu’il y a de fils. La fonction wait()
est fréquement utilisée pour permettre au processus père d’attendre la fin de ses fils avant de se terminer
lui-même.
*/

#define N 3

int count = 0;

int main(int argc, char* argv[]){
	int pid, i=0;
	while(i<N){
		pid=fork();
		if(pid == -1){
			perror("fork");
			exit(0);
		}else if(pid == 0){
			count ++;
			printf("count Fils : %d\n",count );
			break;
			printf("if\n");
		}
		i++;
	}
	if(pid != 0){
		for(i=0; i<N; i++)
			wait(NULL);
		printf("count PERE : %d\n",count );
	}
	return 0;
}