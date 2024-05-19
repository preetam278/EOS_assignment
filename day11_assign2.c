#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
	{
		int arr1[1],arr2[2],ret;
		int a=2,b=7,s;
		ret = pipe(arr1);
		ret = pipe(arr2);
		ret = fork();
		if(ret==0)
			{
			close(arr1[0]);
			close(arr2[1]);
			printf("Enter two number: \n");
			scanf("%d %d",&a, &b);
			write(arr1[1],&a,sizeof(a));
			write(arr1[1],&b,sizeof(b));

			read(arr2[0],&a,sizeof(a));
			printf("Sum: %d\n",a);
			_exit(0);
			}
		else
		{
			close(arr1[1]);
			close(arr2[0]);

			printf("waiting for data...\n");
			read(arr1[0],&a,sizeof(a));
			read(arr1[0],&b,sizeof(b));
			a=a-b;
			write(arr2[1],&a,sizeof(a));

			close(arr2[1]);
			close(arr1[0]);

			waitpid(-1,&s,0);
		}
		return 0;
	}




