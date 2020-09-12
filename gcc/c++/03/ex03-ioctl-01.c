#include<linux/hdreg.h>
#include<stdio.h>
#include<fcntl.h>

static void dump_identity(const struct hd_driveid *id)
  int main(void)
{
  int fd = 0;
  fd = open("/dev/disk/by-id/ate-VMware_Virtual_IDE_CDROM_Drive_100000000000000001",O_RDONLY);
  static struct hd_driveid id;
  if(!ioctl(fd,HDIO_GET_IDENTITY,&id))
    {
      dump_identity(&id);
    }
  else {
    printf("HDIO_GET_IDENTITY failed");
    return 0;
  }


  static void dump_identity(const struct hd_driveid *id)
  {
    const unsigned short int *id_regs = (const void*)id;
    printf("Model=%.40s,FwRev=%.8s,SerialN=%.20s\n",id->model,id->fw_rev,id->serial_no);
  }
}
