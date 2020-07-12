#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

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