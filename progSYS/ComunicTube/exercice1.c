#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>
#include <ctype.h>

/*

Exercice 1
Ecrire le programme C sous Unix qui permet à un processus père de créer un processus Fils. Le fils
récupère une chaine de caractère l’écrit dans un tube. Le père lit du tube caractère par caractère et
l’affiche en majuscule.
Appels Système : fork(), pipe(), read(), write(), close();

*/


#define MAX 25

int main(){
	char buffer[MAX];
	char c;
	int nbc;
	int pid, fd[2];

	//creation du tube
	if(pipe(fd)<0)
		exit(1);
	pid=fork();

	if(pid == -1){
		perror("fork");
		exit(1);
	}
	if(pid == 0){
		close(fd[0]); //on ferme le descripteur de lecture
		printf("Entrer une chaine de caracteres : ");
		scanf("%s", buffer);
		write(fd[1], buffer, strlen(buffer)*sizeof(char));
		close(fd[1]); //on ferme le tube apres avoir terminer l'ecriture
	}else{
		//Le pre
		//wait(NULL);
		close(fd[1]);
		while(read(fd[0], &c,1) != 0){
			printf("%c\n",toupper(c));
		}
		printf("\n");
		close(fd[0]);
	}
	return 0;
}