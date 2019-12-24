#include "my.h"

#define N 10
//3265
int main()
{
	pid_t p1, p2, p3;
	int fd[2], rn, wn, rnn, s1, s2, s3;
	int o=1, p=1;
	char rbuf[20], wbuf[20], rbuff[20];
	memset(rbuf, 0, sizeof(rbuf));
	memset(wbuf, 0, sizeof(wbuf));
	memset(rbuff, 0, sizeof(rbuff));
	
	pipe(fd);

	p1 = fork();
	if(p1<0)
	{
		perror("fork failed at p1\n");
		return -1;
	}
	else if(p1==0)		//child 1
	{
		printf("It's first child %d\n",getpid());
		close(fd[0]);
		sprintf(wbuf, "1");
		for(int i=1;i<N;i++)
		{
			write(fd[1], wbuf, sizeof(wbuf));
		}
		close(fd[1]);
		exit(10);
	}
	else
	{
		p1=wait(&s1);
		p2 = fork();
		if(p2<0)
		{
			perror("fork failed at p2\n");
			return -1;
		}
		else if(p2==0)		//child 2
		{
			printf("It's second child %d\n",getpid());
			sprintf(wbuf, "1");
			while(o<N)
			{
				o++;
				rn=read(fd[0], rbuf, sizeof(rbuf));
				printf("[Second child] read from pipe %d byte.Conten of pipe is %s\n",rn, rbuf);
				if(rn==0)
				{
					printf("Second child read error.\n");
					break;
				}
			}
			sprintf(wbuf, "1");
			for(int l=1;l<N;l++)
			{
				write(fd[1], wbuf, sizeof(wbuf));
			}
			exit(20);
		}
		else
		{
			p2=wait(&s2);
			p3 = fork();
			if(p3<0)
			{
				perror("fork failed at p3\n");
				return -1;
			}
			else if(p3==0)		//child 3
			{
					printf("It's third child %d\n",getpid());
					close(fd[1]);
					while(p<N)
					{	
						p++;
						rnn=read(fd[0], rbuff, sizeof(rbuff));
						printf("[Third child] read from pipe %d byte.Conten of pipe is %s\n",rnn, rbuff);
						if(rnn==0)
						{
							printf("Third child read error.\n");
							break;
						}
					}
					printf("[Third child] has read for %d times\n",p);
					close(fd[0]);
					exit(30);
			}
			else
			{
				p3=wait(&s3);
				printf("%d exit code %d\n%d exit code %d\n%d exit code %d\n", p1, WEXITSTATUS(s1), p2, WEXITSTATUS(s2),p3, WEXITSTATUS(s3));
				return 0;
			}
		}	
	}
}

void sighandler(int signo)
{
	printf("[parent]: parent catch a SIGPIPE signal and signumber = %d\n",signo);
}
