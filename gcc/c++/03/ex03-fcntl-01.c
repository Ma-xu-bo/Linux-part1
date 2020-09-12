#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

int main(void)
{
  int flags = -1;
  int accmode = -1;

  flags = fcntl(0,F_GETFL,0);
  if (flags < 0)
    {
      printf("failure to use fcntl\n");
      return -1;
    }
  accmode = flags & O_ACCMODE;
  if (accmode == O_RDONLY)
    printf("STDIN READ ONLY\n");
  else if (accmode == O_WRONLY)
    printf("STDIN WRITE ONLY\n");
  else if (accmode == O_RDWR)
    printf("STDIN READ WRITE\n");
  else
    printf("STDIN UNKNOWN MODE");
  if (flags & O_APPEND)
    printf("STDIN APPEND\n");
  if (flags & O_NONBLOCK)
    printf("STDIN NONBLOCK\n");
  return 0;
}
