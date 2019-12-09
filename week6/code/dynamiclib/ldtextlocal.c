#include<stdio.h>
#include "dylib.h"

int main()
{
	int a[5] = {23,45,63,-9023,7};
	show(a, 5);
	printf("max = %4d\n",max(a,5));
	printf("sum = %4d\n",sum(a,5));
}
