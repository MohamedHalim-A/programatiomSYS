#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

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