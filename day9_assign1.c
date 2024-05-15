#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int pid,sig_num,ret;
	printf("Enter any PID no :\n");
	scanf("%d",&pid);
	printf("Enter sig_num no :\n");
	scanf("%d",&sig_num);
	ret=kill(pid,sig_num);
	return 0;
}

