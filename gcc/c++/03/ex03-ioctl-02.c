#include<linux/cdrom.h>
#include<stdio.h>
#include<fcntl.h>

int main(void)
{
  int fd = open("/dev/cdrom",O_RDONLY);
  if (fd < 0)
    {
      printf("open cdrom failure\n");
      return -1;
    }
  if(!ioctl(fd,CDROMJECT,NULL))
    {
      printf("eject cdrom success\n");
    }else{
        printf("eject cdrom failure\n");
      }
}
