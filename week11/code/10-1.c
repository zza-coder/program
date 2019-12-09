#include "my.h"

int main()
{
	int pid1, pid2, pid3, status, rv;
/*	FILE *fp;
	char buf[] = {"123456789\n"};
	if((fp=fopen("test.dat","a"))==NULL)
	{
		perror("Failed to fopen!\n");
		return -1;
	}
	if(fputs(buf, fp)==EOF)
	{
		perror("Failed to fputs!\n");
		return -1;
	}
*/	pid1 = fork();
	if(pid1<0)
	{
		perror("fork failed!\n");
		return -1;
	}
	else if(pid1==0)
	{
/*		if((fp=fopen("test.dat","a"))==NULL)
		{
			perror("Failed to fopen!\n");
			return -1;
		}
		if(fputs(buf, fp)==EOF)
		{
			perror("Failed to fputs!\n");
			return -1;
		}
*/		printf("child1 pid = %d\n",getpid());
		sleep(3);
		exit(18);
	}
	else
	{
		printf("parent fork child2!\n");
		pid2 = fork();
		if(pid2<0)
		{
			perror("fork failed!\n");
			return -1;
		}
		else if(pid2==0)
		{
/*			if((fp=fopen("test.dat","a"))==NULL)
			{
				perror("Failed to fopen!\n");
				return -1;
			}
			if(fputs(buf, fp)==EOF)
			{
				perror("Failed to fputs!\n");
				return -1;
			}
*/			printf("child2 pid = %d\n",getpid());
			sleep(5);
			exit(99);
		}	
		else
		{
			printf("parent fork child3!\n");
			pid3 = fork();
			if(pid3<0)
			{
				perror("fork failed!\n");
				return -1;
			}
			else if(pid3==0)
			{
/*				if((fp=fopen("test.dat","a"))==NULL)
				{
					perror("Failed to fopen!\n");
					return -1;
				}
				if(fputs(buf, fp)==EOF)
				{
					perror("Failed to fputs!\n");
					return -1;
				}
*/				printf("child3 pid = %d\n",getpid());
				sleep(5);
				exit(108);
			}	
			else
			{
				printf("parent waitng child end!\n");
				rv = wait(&status);
				printf("1:child %d end.exit code is %d\n", rv, WEXITSTATUS(status));
				rv = 0;
				status = 0;
				rv = waitpid(pid1, &status, 0);												//0 means always waiting
				printf("2:child %d end.exit code is %d\n", rv, WEXITSTATUS(status));
				rv = 0;
				status = 0;
				rv = waitpid(pid2, &status, WNOHANG);
				printf("3:child %d end.exit code is %d\n", rv, WEXITSTATUS(status));
				return 0;
			}
		}	
	
	}
}
