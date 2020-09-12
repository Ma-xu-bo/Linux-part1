#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

int main(void)
{
  int fd = -1;
  char filename[] = "test.txt";
  printf("SSIZE_MAX,%d\n",SSIZE_MAX);
  fd = open(filename,O_RDWR);
  if (-1 == fd)
    {
      printf("Open file %s failure!, fd:%d\n",filename,fd);
    }
  else{
    printf("Open file %s success,fd:%d\n",filename,fd);
  }
  return 0;
}
