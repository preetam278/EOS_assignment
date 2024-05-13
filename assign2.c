#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
  int ret1 = 0,ret2 = 0,ret3 = 0,ret4 = 0,s = 0;
  ret1 = fork();
  if(ret1 == 0)
  {
    ret2 = fork();
    if(ret2 == 0)
    {
      ret3 = fork();
      if(ret3 == 0)
      {
        for(int l = 0;l < 10;l++)
        {
          printf("Process D %d\n",l);
          sleep(1);
        }
        _exit(3);
      }
      for(int k = 0;k<10;k++)
      {
        printf("Process C %d\n",k);
        sleep(1);
      }
      wait(NULL);
      _exit(2);
    }
    for(int j = 0;j<10;j++)
    {
      printf("Process B %d\n",j);
      sleep(1);
    }
     wait(NULL);
    _exit(1);
  }
  for(int i = 0;i<10;i++){
    printf("process A %d\n",i);
    sleep(1);
    }
  wait(NULL);    
  return 0;
}

