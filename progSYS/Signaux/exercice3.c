#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

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