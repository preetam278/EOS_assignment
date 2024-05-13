#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
  int ret = 0,i = 0;
  while(1)
  {
    ret = fork();
    if(ret == 0)
    {
       printf("child\n");
      _exit(0);
    }
    else if(ret == -1)
    break;
    else{
    printf("process count %d\n",i);
    i++;}

  }
  while(i != 0)
  {
    wait(NULL);
    i--;
  }
}
