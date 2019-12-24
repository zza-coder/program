#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<wait.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>

void sighandler(int signo);
