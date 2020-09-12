#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>/*mmap*/
#include<string.h>/*memset warning*/
#include<stdio.h>

#define FILELENGTH 80
int main(void)
{
  int fd = -1;
  char buf[] = "quick brown fox jumps over the lazy dog";
  char *ptr =NULL;

  /*打开mmap.txt,并且将文件长度缩小为0.如果文件不存在则创建它，权限为可读写执行*/
  fd = open("mmap.txt",O_RDWR|O_CREAT|O_TRUNC,S_IRWXU);
  if(-1 == fd)
    {
      return -1;
    }

  lseek(fd,FILELENGTH-1,SEEK_SET);
  write(fd,'a',1);

  ptr = (char*)mmap(NULL,FILELENGTH,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
  if ((char*)-1 ==ptr)
    {
      printf("mmap failure\n");
      close(fd);
      return -1;
    }

  memcpy(ptr+16, buf, strlen(buf));
  munmap(ptr,FILELENGTH);
  close(fd);
  return 0;
}
