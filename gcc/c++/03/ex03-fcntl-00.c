#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>

#define NEWFD 8
int main(void)
{
  char buf[] = "FCNTL";
  int fd = open("test.txt",O_RDWR);
  printf("the file test.txt ID is %d\n",fd );

  fd = fcntl(fd, F_GETFD);
  printf("the file test.txt ID is %d\n",fd);
  fd = NEWFD;
  fcntl(NEWFD,F_SETFD,&fd);

  write(NEWFD, buf ,strlen(buf));
  close(NEWFD);
  return 0;
}
