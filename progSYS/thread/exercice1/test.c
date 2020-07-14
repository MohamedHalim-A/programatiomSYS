#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void* myturn(void* arg){
	for(int i=0; i<10; i++){
		sleep(1);
		printf("c'est mon tour ! n° %d\n", i+1);
	}
	pthread_exit(NULL); // terminaison d'un thread
}

void yourturn(){
	for(int i = 0; i<3 ; i++){
		sleep(2);
		printf("Hey ! c'est TON tour ! n° %d\n", i+1);
	}
}

int main(){
	pthread_t thread1;
	pthread_create(&thread1, NULL, myturn, NULL);
	yourturn();
	pthread_exit(NULL); // terminaison du thread principal 'main'
}