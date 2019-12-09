#include "my.h"

int main()  
{

  	int g = 0, t = 0, s = 0;
  	pid_t pid;
 	printf("before vfork\n");
  	if((pid=vfork())<0)
	{
   		perror("create failure");
		exit(-1);
 	}
	else if(pid==0)
	{
		printf("before child pid = %d, &g = %p, &t = %p, &s = %p\n", getpid(), &g,&t,&s);
		g = 100;
		t = 200;
		s = 300;
		printf("after child pid = %d, &g = %d, &t = %d, &s = %d\n", getpid(), g,t,s);
  	}
	else
	{
   		printf("parent pid = %d, &g = %p, &t = %p, &s = %p\n", getpid(), &g,&t,&s);
		printf("parent pid = %d, &g = %d, &t = %d, &s = %d\n", getpid(), g,t,s);
		return 0;
  	}

}  
