#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <wait.h>

int main(int argc, char *argv[]){
	int pid, tube[2];
	if(pipe(tube) == -1){
		perror("pipe");
		exit(1);
	}
	pid=fork();

	if(pid == -1){
		perror("fork");
		exit(1);
	}
	if(pid == 0){
		close(tube[1]);
		dup2(tube[0],0); //connection du tube avec stdin
		close(tube[0]);
		//execution des commandes shell
		execlp("wc", "wc", "-l",(char *)NULL);
	}else{
		close(tube[0]);
		dup2(tube[1],1); //connection du tube avec le stdout
		close(tube[1]);
		//execution de la commande shell ps -A
		execlp("ps", "ps", "-A", (char *)NULL);
	}
	return 0;
}