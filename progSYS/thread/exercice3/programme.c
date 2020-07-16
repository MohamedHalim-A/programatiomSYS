#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define NMAX 9

/*
Exercice 3 :
Le but est de faire coopérer deux threads pour déterminer tous les
 entiers ≥ 10 dans un tableau.
Écrire un programme dans lequel:
1. le thread principal crée deux thread fils «thread1» et «thread2».
2. le thread «thread1» détermine tous les entiers ≥ 10 dans la
 première moitié du tableau.
3. le thread «thread2» détermine tous les entiers ≥ 10 dans la
 deuxième moitié du tableau.

8

4. Le thread principal collecte les deux résultats et affiche 
le résultat final

*/

int tab[NMAX] = {12,7,6,44,49,23,5, 99,7};
int tabres1[NMAX], tabres2[NMAX];

/****
*La 1ere fonction cherche les valeurs >=0 dans la parti 1 du tableau
***/
void* fcttab1(void* threadindex){
	int* fin = (int*)threadindex;
	int i=0;

	//calcule des nombre >=10
	int* dimention1 = (int*)malloc(sizeof(int));
	*dimention1=0;

	for(i=0; i<*fin; i++){
		if(tab[i] >= 10){
			tabres1[*dimention1] = tab[i];
			//printf("%d ",tabres1[i] );
			(*dimention1)++;
		}
	}
	printf("\n");

	return dimention1;
}

/****
*La 2eme fonction
**/
void* fcttab2(void* threadindex){
	int j;
	int* debut = (int*)threadindex;

	int* dimention2 = (int*)malloc(sizeof(int));
	*dimention2=0;

	for(j=NMAX-1; j >= *debut; j--){
		if(tab[j] >= 10){
			tabres2[*dimention2] = tab[j];
			//printf("%d ",tabres1[i] );
			(*dimention2)++;
		}
	}
	printf("\n");

	return dimention2;
}

int main(int argc, char* argv[]){

	pthread_t threads1, threads2;
	int r1, r2;
	int *result1, *result2;
	int debut, fin;

	fin = NMAX/2;
	debut = fin;

	r1 = pthread_create(&threads1, NULL, fcttab1, (void*)&fin);
	r2 = pthread_create(&threads2, NULL, fcttab2, (void*)&debut);

	if(r1 != 0){
		printf("Error : pthread_create() returned %d\n", r1);
		exit(-1);
	}
	if(r2 != 0){
		printf("Error : pthread_create() returned %d\n", r2);
		exit(-1);
	}

	pthread_join(threads1, (void*)&result1);
	pthread_join(threads2, (void*)&result2);

	printf("\n");

	//affiche les eklement de la premiere moitie
	printf("Valeur >= 10 du 1er partie du tableau : ");
	for(int i=0; i < *result1; i++)
		printf(" %d  ", tabres1[i]);

	printf("\n");

	//affiche les element de la deuxieme partie
	printf("Valeur >= 10 du 2eme partie du tableau : ");
	for(int i=0; i < *result2; i++)
		printf(" %d  ", tabres2[i]);
	printf("\n");

	pthread_exit(NULL);
}