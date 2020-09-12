#include<sts/types.h>
#include<unistd.h>
#include<stdio.h>

int main()
{
  pid_t pid,ppid;
  pid = getpid();
  ppid = getppid();

  printf("当前进程的ID号为：%d\n",pid);
  printf("当前进程的父进程ID号为：%d\n",ppid);
  return 0;
    
}
