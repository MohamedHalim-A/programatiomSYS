#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

/*
Exercice 5 :
1. Commenter, ligne par ligne, le programme ci-dessous
2. Dire ce qui est affiché à l’écran pendant l’exécution du programme signaux.c. Expliquez votre
réponse.
3. Modifier votre programme de tel façon à obliger le fils par commencer le premier.

*/

void message(int signum){
	printf("Message recue %d, %d \n", getpid(), signum);
}

int main(void){
	int c_pid, sig;
	struct sigaction action;
	action.sa_handler=message;
	action.sa_flags=0;

	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGINT, &action, NULL);

	if(c_pid=fork()){
		sigset_t ens1, ens;
		printf("\n Valeur de retour du Pere : %d son PID %d \n", c_pid, getpid());

		sigemptyset(&ens);
		sigaddset(&ens, SIGUSR1);
		sigaddset(&ens, SIGINT);
		sigprocmask(SIG_SETMASK, &ens, NULL);

		kill(getpid(), SIGUSR1);

		sigpending(&ens1);
		for(sig=1; sig<NSIG; sig++)
			if(sigismember(&ens1, sig))
				printf("\n message pendant %d \n", sig);
			putchar("\n");
		sleep(5);

		sigemptyset(&ens);
		sigprocmask(SIG_SETMASK, &ens, NULL);
	}else{
		printf("Valeur du retour du fork %d \n",c_pid);
		printf("son PID : %d \n",getpid());
		printf("le PID de son PERE : %d \n",getppid());
		sleep(1);
		kill(getppid(), SIGINT);
		sleep(1);
	}
	return 0;
}
/*
struct sigaction action;
action.sa_handler = message;
action.sa_flags = 0;
sigemptyset(&action.sa_mask);
• Création de la structure sigaction qui décrit le gestionnaire de signaux et nous appelons sigaction()
avec cette structure pour gérer un signal.
• Dans le champ sa_handler, nous précisons la fonction qui sera appelée (le nouveau comportement
redéfini pour un signal donné).

6

• Le masque que nous indiquons dans sa_mask spécifie les signaux que nous ne souhaitons pas
capter pendant l’exécution de la fonction de traitement du signal. En vidant ce masque avec la
fonction sigemptyset(), nous signifions au système que tous les signaux pouvant survenir pendant
une interruption sont à mettre en attente.
sigaction(SIGUSR1, &action, NULL);
sigaction(SIGINT, &action, NULL);
• Nous gérons le signal SIGINT et le signal SIGUSR1 avec la fonction sigaction
if( c_pid = fork())
• l’appel système fork() Duplique le processus courant en créant un processus fils
• Donc après le fork(), on a deux processus : un processus père (quand le fork retourne le pid du
fils) et un processus fils (la valeur de retour du fork est 0);
• Quand la condition est vraie, le parent exécute l’instruction if et le fils exécute le else.
Donc, dans le père :
sigset_t ens1, ens;
printf("Valeur de retour du Père: %d son PID %d. ", c_pid, getpid());
sigemptyset(&ens);
sigaddset(&ens, SIGUSR1);
sigaddset(&ens, SIGINT);
sigprocmask(SIG_SETMASK, &ens, NULL);
• Initialise l’ensemble des signaux qu’on veut masquer avec sigemptyset() (l’ensemble vide). c à d ens
= . (attention, une simple initialisation du genre ens = ne suffit pas; il faut utiliser la fonction
sigemptyset).

• Après on appelle la fonction sigaddset() pour ajouter les signaux (SIGUSR1, SIGINT) à cet en-
semble. ( celà dit l’ensemble est ens = SIGUSR1, SIGINT)

• Appel de sigprocmask() pour installer le masque avec pour premier argument la valeur : SIG_SETMASK
pour remplacer l’ancien masque ; le second argument de la fonction sigprocmask() est un pointeur
sur le masque que nous venons de créer, i.e. ens = SIGUSR1, SIGINT
kill(getpid(), SIGUSR1);
• Envoie d’un signal du processus à lui-même. Ce signal sera masqué puisque SIGUSR1 appartient
au masque installé
sigpending(&ens1);
for(sig = 1; sig < NSIG; sig++)
if(sigismember(&ens1, sig))
printf(" message pendant %d ", sig);
putchar(”);
sleep(5);

• Pour vérifier qu’un signal a été bloqué et est en attente d’être traité. On utilise la fonction sig-
pending() qui vérifie avec sigismember() si le masque contient le(s) signal(s) en question.

• l’appel système sleep() permet au processus de s’endormir 5 secondes

7

sigemptyset(&ens) sigprocmask(SIG_SETMASK, &ens, NULL);
• réinitialiser (vider) l’ensemble des signaux à masquer
• Reinstaller un nouveau masque (l’ensemble vide, aucun processus à mettre en attente). Cela permet
de débloquer/délivrer les signaux qui ont été masqué
Dans le Fils :
else
....
kill(getppid(), SIGINT);
• Envoie le signal SIGINT au père avec la fonction kill(getpid(), SIGINT). (Le comportement du
signal est redéfini à l’aide du gestionnaire de signaux sigaction).
*/