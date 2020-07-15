#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void* myturn(void* arg){
	int i=0;
	while(1){
		sleep(1);
		printf("c'est mon tour ! n°%d\n", i+1);
	}
	pthread_exit(NULL);
}

void yourturn(){
	while(1){
		int i;
		sleep(2);
		printf("Hey ! c'est TON tour ! n°%d\n", i+1);
	}
}
int main(){
	pthread_t thread1;
	pthread_create(&thread1, NULL, myturn, NULL);
	yourturn();

	pthread_exit(NULL);
}
