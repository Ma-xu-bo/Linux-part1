#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

int main(void)
{
  int fd = -1;
  char filename[] = "/dev/sda1";
  fd = open(filename,O_RDONLY);
  if(fd == -1)
    {
      printf("Open file %s failure\n!,fd:%d\n",filename,fd );
    }
  else {
    printf("Open file %s success,fd%d\n",filename,fd);
  }
  return 0;
}
