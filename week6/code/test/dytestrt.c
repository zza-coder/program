#include<stdio.h>
#include<stdlib.h>
#include<dlfcn.h>
#include "dylib.h"

int main()
{
	void *hd;
	void (*f1)();
	int (*f2)(), (*f3)();
	char *error;
	int a[5] = {23,45,63,-9023,7};
	hd = dlopen("../dynamiclib/libdylib.so",RTLD_LAZY);
	if(!hd)
	{
		fprintf(stderr, "%s\n",dlerror());
		exit(1);
	}
	f1 = dlsym(hd, "show");
	if((error = dlerror())!=NULL)
	{
		fprintf(stderr, "%s\n",dlerror());
		exit(1);
	}
	f2 = dlsym(hd, "max");
	if((error = dlerror())!=NULL)
	{
		fprintf(stderr, "%s\n",dlerror());
		exit(1);
	}
	f3 = dlsym(hd, "sum");
	if((error = dlerror())!=NULL)
	{
		fprintf(stderr, "%s\n",dlerror());
		exit(1);
	}
	f1(a, 5);
	printf("max = %4d\n",f2(a,5));
	printf("sum = %4d\n",f3(a,5));
	if(dlclose(hd)<0)
	{
		fprintf(stderr, "%s\n",dlerror());
		exit(1);
	}

	return 0;
}
