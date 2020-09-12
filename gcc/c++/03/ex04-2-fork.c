#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(void)
{
  pid_t pid;
  pid = fork();

  if(-1 == pid)
    {
      printf("进程创建失败！\n");
      return -1;
    }
  else if(pid == 0)
    {
      printf("子进程，fork返回至：%d, ID:%d 父进程ID:%d\n",pid,getpid(),getppid());
      
    }
  return 0;
}
