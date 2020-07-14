#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void myturn(){
	int i=0;
	while(1){
		sleep(1);
		printf("c'est mon tour ! n°%d \n", i+1);
	}
}

void yourturn(){
	int i=0;
	while(1){
		sleep(2);
		printf("Hey ! c'est TON tour n°%d\n", i+1);
	}
	pthread_exit(NULL);
}


int main(){
	myturn();
	yourturn();

	return 0;
}