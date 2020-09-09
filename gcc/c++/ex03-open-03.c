#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
int main(void){
  int fd = -1,i;
  ssize_t size = -1;
  char buf[10];
  char filename[] = "text.txt";

  fd = open(filename,O_RDONLY);
  if (-1 == fd){
    printf("Open file %s failure,fd:%d\n",filename, fd );
  }else {
    printf("Open file %s success,fd:%d\n",filename,fd);
  }

  while(size){
    size = read(fd, buf, 10);
    if (-1 == size)
      {
	close(fd);
	printf("read file error occurs\n");
	return -1;}


    
    else{ 
      if(size >0){
	printf("read %d bytes:",size);
	printf("\"");
	for(i=0;i<size;i++){ printf("%c",*(buf+i));}
	printf("\"\n");
      }else{      
      printf("reach the end of file\n");
    }
  }
    
  }
  return 0;
}
