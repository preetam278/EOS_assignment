#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

//p2 -- reader
int  main()
{
	int fdr,fdw,a,b,sum;

	fdr = open("/home/superuser/desd_client", O_RDONLY);
	printf("\nwaiting for data...\n");

	read(fdr,&a,sizeof(int));
	read(fdr,&b,sizeof(int));
	printf("\nreading data...\n\n");
	printf("A -> %d\t B -> %d\n\n",a,b);

	sum=a+b;

	fdw = open("/home/superuse/desd_server",O_WRONLY);
	printf("returning data...\n");

	write(fdw,&sum,sizeof(int));

	close(fdr);
	close(fdw);

	return 0;
}

