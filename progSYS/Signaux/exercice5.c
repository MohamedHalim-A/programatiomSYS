#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

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