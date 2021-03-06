#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void* myturn(void* arg){
	int* n = (int*)arg;

	for(int i=0; i<10; i++){
		sleep(2);
		printf("c'est mon tour ! n° %d %d\n", i+1, (*n)++);
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
	int myturn_arg =17;

	//creation du thread avec passage de l,argument myturn_arg a la fonction myturn
	pthread_create(&thread1, NULL, myturn, (void*)&myturn_arg);

	yourturn();
	pthread_join(thread1, NULL);

	//affichage de la valeur de myturn_arg apres le thread1
	printf("Apres terminaison du thread1, myturn_arg = %d\n", myturn_arg);

	pthread_exit(NULL); // terminaison du thread principal 'main'
}
/*

3. Comment faire pour que le thread créé continue l’exécution de toutes les tours de boucles.
Il faut utiliser la fonction pthread_join(thread1, NULL). (NULL parce que la fonction myturn()
appelée par le thread1 ne retourne aucune valeur). La fonction pthread_join permet d’attendre
jusqu’à ce qu’un thread spécifique (ici thread1 ) termine son exécution.

#include<pthread.h>
#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>
void* myturn(void* arg){
for(int i = 0; i<10 ; i++){
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
pthread_join(thread1, NULL);
pthread_exit(NULL); // terminaison du thread principal 'main'
}

*/