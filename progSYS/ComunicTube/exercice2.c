#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <unistd.h>

/*

Exercice 2 : Synchronisation Père/Fils

Ecrire le programme C sous Unix qui permet à un 
processus père de créer un processus Fils. Le père
et le Fils doivent s’exécuter en parallèle et 
permettent l’affichage suivant :
Fils: 2 4 6 8 10
Père: 13 16 19 22 25
Appels Systèmes : fork(), pipe()

*/

int main(){
	int pid, i=1;
	int tube[2];
	int n1;
	pipe(tube);

	pid = fork();
	
		if(pid == -1){
			perror("fork");
			exit(-1);

		}else if(pid == 0){
			printf("Fils : \t");
			do{
				n1=i*2;
				printf("%d  ",n1);
				i++;
			}while(n1%5 != 0);
			close(tube[0]);
			write(tube[1], &n1, 1*sizeof(int));
			close(tube[1]);
			printf("\n");
		}else{
			wait(NULL);
			printf("Pere :\t");
			close(tube[1]);
			read(tube[0], &n1, 1*sizeof(int));
			do{
				n1 +=3;
				printf("%d  ",n1);
			}while(n1%5 != 0);
			close(tube[0]);
			printf("\n");
		}	
	
}