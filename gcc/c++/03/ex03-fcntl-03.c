#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

#define NEWFD 8

int main(void)
{
  int uid;
  int fd = open("test.txt",O_RDWR);

  uid = fcntl(fd,F_GETOWN);
  printf("the SIG recv ID is %d\n",uid);
  close(fd);
  return 0;
}
