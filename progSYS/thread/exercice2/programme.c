#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_THREADS 4

/*

Exercice 2 :
Ecrire un programme dans lequel:
• Le thread principal (fonction « main() ») crée deux threads.
• Le premier thread affiche «nb1» fois une lettre donnée.
• Le deuxième thread affiche «nb2» fois une autre lettre donnée.

*/

struct data{
	int count;
	char c;
};

void* affiche(void* k){
	struct data* p =(struct data*)k;
	int i;

	for(i=0; i<(int)((*p).count); i++){
		fputc((int)(*p).c, stderr); //afiche le caractere reperer ((*p).cont) fois	
	}
	pthread_exit(NULL);
}

int main(){
	pthread_t thread_id1, thread_id2;

	struct data arg1, arg2;

	arg1.count = 40;
	arg1.c = 'a';

	arg2.count = 100;
	arg2.c = 'b';

	pthread_create(&thread_id1, NULL, affiche, &arg1);
	pthread_create(&thread_id2, NULL, affiche, &arg2);

	pthread_join(thread_id1, NULL);
	pthread_join(thread_id2, NULL);

	pthread_exit(NULL);
}