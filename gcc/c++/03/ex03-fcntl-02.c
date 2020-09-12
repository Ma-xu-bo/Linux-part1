#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<string,h>

int main(void)
{
  int flags = -1;
  char buf[] = "FCNTL";

  int fd = open("test.txt",O_RDWR);
  flags = fcntl(fd,F_GETFL,0);
  flags |= O_APPEND;
  flags = fcntl(fd,F_GETFL,&flags);
  if (flags <0)
    {
      printf("failure to use fcntl\n");
      return -1;
    }
  write(fd,buf,strlen(buf));
  close(fd);
  return 0;
}
