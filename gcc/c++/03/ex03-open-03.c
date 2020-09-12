#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

int main(void)
{
  int fd = -1;
  char filename[] = "test.txt";
  fd = open(filename,O_RDWR|O_CREAT|O_EXCL,S_IRWUX);
  if (-1 == fd)
    {
      printf("File %s exist!,reopen it",filename);
      fd = open(filename,O_RDWR);
      printf("fd:%d\n",fd);
      else {
	printf("Open file %s success,fd:%d\n",filename,fd)
	  }
    }
  return 0;
}
