#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
int main(void){
  int fd = -1, i;
  ssize_t size = -1;
  int input = 0;
  char buf[] = "quick brown fox jumps over the lazy dog";
  char filename[] = "test.txt";
  fd = open(filename,O_RDWR|O_TRUNC);
  if (-1 == fd){
    printf("Open file %s failure,fd:%d\n",filename,fd );
  } else {
    printf("open file %s success,fd:%d",filename,fd);
  }
  size = write(fd, buf, strlen(buf));
  printf("write %d bytes to file %s\n",size, filename);
  close(fd);
  return 0;
}
