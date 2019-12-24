#include "my.h"

int num1[100], num2[100], max1, max2, max;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_rwlock_t rwlock;

void randNum(int *n)
{
	int i;
	for(i=0;i<100;i++)
	{
		n[i]=rand()%100;
	}
}

void *fun1(void *param)
{
	int i, temp = num1[0];
	pthread_rwlock_rdlock(&rwlock);
	for(i=1;i<100;i++)
	{
		pthread_mutex_lock(&mutex);
		if(num1[i]>temp)
		temp = num1[i];
		pthread_mutex_unlock(&mutex);
	}
	pthread_rwlock_unlock(&rwlock);
	max1 = temp;
	return NULL;
}


void *fun2(void *param)
{
	int i, temp = num2[0];
	pthread_rwlock_rdlock(&rwlock);
	for(i=1;i<100;i++)
	{
		pthread_mutex_lock(&mutex);
		if(num2[i]>temp)
		temp = num2[i];
		pthread_mutex_unlock(&mutex);
	}
	pthread_rwlock_unlock(&rwlock);
	max2 = temp;
	return NULL;
}



int main()
{
	pthread_t tid[NUM];
	int i, ret;
	randNum(num1);
	randNum(num2);
    ret = pthread_rwlock_init(&rwlock, NULL);
	if(ret)
	{
		perror("rwlock init failed!\n");
		exit(1);
	}	
	pthread_rwlock_wrlock(&rwlock);
	ret = pthread_create(&tid[i],NULL,fun1,NULL);
	if(ret!=0)
	{
		perror("thread init failed!\n");
		exit(2);
	}
	ret = pthread_create(&tid[i],NULL,fun2,NULL);
	if(ret!=0)
	{
		perror("thread init failed!\n");
		exit(2);
	}
	pthread_rwlock_unlock(&rwlock);
	for(i=0;i<NUM;i++)
	{
		pthread_join(tid[i],NULL);
	}
	pthread_rwlock_destroy(&rwlock);
	pthread_mutex_destroy(&mutex);
	if(max1>=max2)
	max=max1;
	else
	max=max2;
	printf("max num-------------------%d\n",max);
}
