#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
int main(void){

  int result = -1;
  int fd[2],nbytes;
  pid_t pid;
  char string[] = "你好，管道";
  char readbuffer[80];

  int *write_fd = &fd[1];
  int *read_fd = &fd[0];

  result = pipe(fd);
  if (-1 == result)
    {
      printf("建立管道失败！\n");
      return -1;
    }
  pid = fork();
  if (-1 == pid)
    {
      printf("fork进程失败！");
      return -1;
    }
  if (0 == pid)
    {
      close(*read_fd);
      result = write(*write_fd,string,strlen(string));
      return 0;
    }
  else {
    close(*write_fd);
    nbytes = read(*read_fd,readbuffer,sizeof(readbuffer));
    printf("接收到 %d 个数据，内容为：%s \n",nbytes,readbuffer);

  }
  return 0;
}
  
