#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*

Exercice 4: (Signaux pendants)
Vérifier quels sont les signaux qui ont été envoyés à un processus mais qui n’ont pas encore été pris
en compte par le processus.
Appel système : sigaddset, sigemptyset, sigprocmask, sigismember, sigpending.
1. Ecrivez un programme en C qui masque les signaux SIGINT et SIGQUIT. Le programme doit alors
s’endormir (fonction sleep).
Pendant qu’il dort, envoyez-lui à partir d’un terminal (kill –SIG < pidprocessus >) un SIGINT
et un SIGQUIT. Lorsque le processus se réveille, il affichera la liste des signaux qui se trouvent
pendants.
2. Modifiez le programme de la question précédente de telle sorte à effacer le masque des signaux pour
SIGINT et SIGQUIT après l’affichage de la liste des signaux pendants.
Est-ce que le processus s’exécutera jusqu’à la fin ? Pourquoi ? Pour vérifier ce comportement
ajoutez à la fin de votre programme l’affichage d’un message quelconque.

*/

int main(){
	sigset_t ens, ens1;
	int sig;

	sigemptyset(&ens);

	sigaddset(&ens, SIGQUIT);
	sigaddset(&ens, SIGINT);

	sigprocmask(SIG_SETMASK, &ens, NULL);

	sleep(10);

	sigpending(&ens1);

	for(sig=1; sig<NSIG; sig++)
		if(sigismember(&ens1, sig))
			printf("sig %d \n",sig);

	/********** QUESTION 2 **********/
	sigemptyset(&ens);
	sigprocmask(SIG_SETMASK, &ens, NULL);

	printf("Message : Programme Trmine");
}
/*

Dans le premier terminal, vous exécutez votre programme exp (./nomExecutable)
• Dans un deuxième terminal :
– Vous lancez la commande ps -a pour lister les processus (vous récupérer le pid de votre
exécutable)
– kill -SIGINT process-PID
– kill -SIGQUIT process-PID
2. Non, le programme ne se termine pas jusqu’à la fin; si l’on ajoute un message à la fin, il ne
sera pas afficher. Ceci est dû au fait que l’on a initialisé l’ensemble des signaux qu’on a passé

5

au masque sigprocmask(SIG_SETMASK, &ens, NULL), à l’ensemble vide avec l’appel système
sigemptyset(&ens). (le nouveau ensemble de signaux bloqués est devenu vide.)
Par conséquent les deux signaux SIGINT et SIGQUIT ont été débloqués et interrompe l’exécution
du programme.

*/