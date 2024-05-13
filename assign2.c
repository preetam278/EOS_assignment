#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
int ret1,ret2,ret3,s1,s2,s3,i;
  ret1 = fork();
  if(ret1 == 0)
  {
	  ret2 = fork();
	  if(ret2 == 0)
	  {
		  ret3 = fork();
		  if(ret3 == 0)
		  {
			  printf("child B: %d\n",i);
			  sleep(1);
			  _exit(0);
		  }
		  printf("child C: %d\n",i);

		  waitpid(ret3,&s3,0);
		 printf("child exit: %d\n", WEXITSTATUS(s3));
		 _exit(0);
	  }
			printf("child D: %d\n",i);
			waitpid(ret2,&s2,0);
			printf("child exit %d\n", WEXITSTATUS(s2));
			_exit(0);
  }
  printf("parent A: %d\n",i);
  waitpid(ret1,&s1,0);
  printf("child exit:%d\n", WEXITSTATUS(s1));
  _exit(0);

}

