#include "test.h"
int main()
{
	sigset_t base_mask,waiting_mask,oldmask;
	int sig;
	sigemptyset(&base_mask);
	sigaddset(&base_mask,SIGQUIT);
	sigaddset(&base_mask,SIGINT);
	if(sigprocmask(SIG_BLOCK,&base_mask,&oldmask)<0){
		/*printf("SIG_BLOCK error\n");
		exit(1);*/
		err_exit("SIG_BLOCK error");
	}
	printf("I have blocked SIFQUIT and SIGINT,and\nyou can try"
             " to send these two signals and wait for my reply.\n");
	sleep(10);
	printf("Let me see if there is any something signal.\n");
	sigpending(&waiting_mask);
	for(sig=1;sig<NSIG;sig++)
		if(sigismember (&waiting_mask,sig)){
			psignal(sig,"there is a pending signal");
		}
	if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0){
		err_exit("SIG_SETMASK error");
		//exit(2);
	}
	printf("there is no suspending signal.BYE!\n");
	exit(EXIT_SUCCESS);
}
